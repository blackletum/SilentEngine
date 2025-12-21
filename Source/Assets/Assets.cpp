#include "Framework.h"
#include "Assets/Assets.h"

#include "Application.h"
#include "Assets/Parsers/Tim.h"
#include "Assets/Parsers/Tmd.h"
#include "Utils/Parallel.h"
#include "Utils/Utils.h"

using namespace Silent::Utils;

namespace Silent::Assets
{
    static const auto ASSET_TYPES = std::unordered_map<std::string, AssetType>
    {
        { ".TIM", AssetType::Tim },
        { ".VAB", AssetType::Vab },
        { ".BIN", AssetType::Bin },
        { ".DMS", AssetType::Dms },
        { ".ANM", AssetType::Anm },
        { ".PLM", AssetType::Plm },
        { ".IPD", AssetType::Ipd },
        { ".ILM", AssetType::Ilm },
        { ".TMD", AssetType::Tmd },
        { ".DAT", AssetType::Dat },
        { ".KDT", AssetType::Kdt },
        { ".CMP", AssetType::Cmp },
        { "",     AssetType::Xa  } // @todo Should be given .XA extension when exporting from ROM.
    };

    static const auto PARSER_FUNCS = std::unordered_map<AssetType, std::function<std::shared_ptr<void>(const std::filesystem::path& file)>>
    {
        { AssetType::Tim, ParseTim },
        { AssetType::Tmd, ParseTmd }
    };

    const std::string& AssetManager::GetName(int assetIdx) const
    {
        // Find name.
        const auto* name = Find(_names, assetIdx);
        if (name == nullptr)
        {
            Debug::Log(Fmt("Attempted to get name of invalid streamable asset {}.", assetIdx), Debug::LogLevel::Warning, Debug::LogMode::Debug);
            return EMPTY_STRING;
        }

        return *name;
    }

    std::vector<std::string> AssetManager::GetLoadedNames() const
    {
        // Run through registered assets.
        auto names = std::vector<std::string>{};
        for (const auto& [keyName, asset] : _assets)
        {
            if (asset->State == AssetState::Loaded)
            {
                names.push_back(asset->Name);
            }
        }

        // Sort names.
        Sort(names);
        return names;
    }

    const std::shared_ptr<Asset> AssetManager::GetAsset(const std::string& assetName)
    {
        // Find asset.
        const auto* assetPtr = Find(_assets, assetName);
        if (assetPtr == nullptr)
        {
            Debug::Log(Fmt("Attempted to get invalid streamable asset `{}`.", assetName), Debug::LogLevel::Warning, Debug::LogMode::Debug);
            return nullptr;
        }
        auto asset = *assetPtr;

        // Load if not preloaded.
        if (asset->State != AssetState::Loaded)
        {
            Debug::Log(Fmt("Streamable asset `{}` was not preloaded.", assetName),
                       Debug::LogLevel::Warning, Debug::LogMode::Debug);

            Load(assetName).wait();
        }

        // Check if loading failed.
        if (asset->State == AssetState::Error)
        {
            Debug::Log(Fmt("Failed to get streamable asset `{}`.", assetName), Debug::LogLevel::Error, Debug::LogMode::Debug);
            return nullptr;
        }

        return asset;
    }

    bool AssetManager::IsBusy() const
    {
        return _loadingCount > 0;
    }

    void AssetManager::Initialize(const std::filesystem::path& assetsPath)
    {
        // Collect files sorted alphabetically.
        auto files = std::vector<std::filesystem::path>{};
        for (auto& entry : std::filesystem::recursive_directory_iterator(assetsPath))
        {
            if (entry.is_regular_file())
            {
                files.push_back(entry.path());
            }
        }
        Sort(files);

        // Register assets.
        _assets.reserve(files.size());
        for (int i = 0; i < files.size(); i++)
        {
            const auto& file = files[i];

            // Check if type is streamable.
            auto ext = ToUpper(file.extension().string());
            if (Find(ASSET_TYPES, ext) == nullptr)
            {
                //Debug::Log(Fmt("Attempted to register non-stremable asset for file `{}`.", file.string()), Debug::LogLevel::Warning, Debug::LogMode::Debug);
                continue;
            }

            // @heapalloc Create asset entry.
            auto name = std::filesystem::relative(file, assetsPath).string();
            _assets.emplace(name, std::make_shared<Asset>());

            // Define asset entry.
            auto asset   = _assets[name];
            asset->Name  = name;
            asset->Type  = ASSET_TYPES.at(ext);
            asset->File  = file;
            asset->Size  = std::filesystem::file_size(file);
            asset->State = AssetState::Unloaded;
            asset->Data  = nullptr;

            // Add asset name to maps.
            _names[i] = asset->Name;
        }

        // Create fallback ready future.
        _loadFutures[EMPTY_STRING] = GenerateReadyFuture();

        Debug::Log(Fmt("Registered {} streamable assets.", _assets.size()), Debug::LogLevel::Info, Debug::LogMode::Debug);
    }

    const std::future<void>& AssetManager::Load(const std::string& assetName)
    {
        auto& executor = g_App.GetExecutor();

        // Find asset.
        const auto* assetPtr = Find(_assets, assetName);
        if (assetPtr == nullptr)
        {
            Debug::Log(Fmt("Attempted to load unregistered streamable asset `{}`.", assetName), Debug::LogLevel::Warning, Debug::LogMode::Debug);
            return _loadFutures[EMPTY_STRING];
        }
        auto asset = *assetPtr;

        // Check if loading or loaded.
        if (asset->State == AssetState::Loading || asset->State == AssetState::Loaded)
        {
            return _loadFutures[assetName];
        }

        // Check if file is valid.
        if (!std::filesystem::exists(asset->File))
        {
            Debug::Log(Fmt("Attempted to load streamable asset `{}` from invalid file `{}`.", asset->Name, asset->File.string()),
                       Debug::LogLevel::Error, Debug::LogMode::Debug);

            asset->State = AssetState::Error;
            return _loadFutures[assetName];
        }

        // Set loading state.
        asset->State = AssetState::Loading;
        _loadingCount++;

        // Load asynchronously.
        _loadFutures[assetName] = executor.AddTask([&]()
        {
            // Get parser function.
            const auto* parserFunc = Find(PARSER_FUNCS, asset->Type);
            if (parserFunc == nullptr)
            {
                Debug::Log(Fmt("Attempted to load streamable asset `{}` with no parser function for asset type {}.", asset->Name, (int)asset->Type),
                           Debug::LogLevel::Error);

                asset->State = AssetState::Unloaded;
                _loadingCount--;
                return;
            }

            // Parse asset data from file.
            try
            {
                asset->Data  = (*parserFunc)(asset->File);
                asset->State = AssetState::Loaded;

                Debug::Log(Fmt("Loaded streamable asset `{}`.", asset->Name), Debug::LogLevel::Info, Debug::LogMode::Debug);
            }
            catch (const std::exception& ex)
            {
                asset->Data  = nullptr;
                asset->State = AssetState::Error;

                Debug::Log(Fmt("Failed to parse file for streamable asset `{}`: {}", asset->Name, ex.what()), Debug::LogLevel::Error);
            }
            _loadingCount--;
        });

        return _loadFutures[assetName];
    }

    void AssetManager::Unload(const std::string& assetName)
    {
        // Find asset.
        const auto* assetPtr = Find(_assets, assetName);
        if (assetPtr == nullptr)
        {
            Debug::Log(Fmt("Attempted to unload unregistered streamable asset `{}`.", assetName), Debug::LogLevel::Warning, Debug::LogMode::Debug);
            return;
        }
        auto asset = *assetPtr;

        // Check if already unloaded.
        if (asset->State == AssetState::Unloaded)
        {
            return;
        }

        // Unload.
        asset->State = AssetState::Unloaded;
        asset->Data  = nullptr;

        // Remove load future.
        _loadFutures.erase(assetName);

        Debug::Log(Fmt("Unloaded streamable asset `{}`.", assetName), Debug::LogLevel::Info, Debug::LogMode::Debug);
    }

    void AssetManager::UnloadAllAssets()
    {
        // Run through registered assets.
        for (auto& [keyName, asset] : _assets)
        {
            if (asset->State == AssetState::Unloaded)
            {
                continue;
            }

            // Unload.
            asset->State = AssetState::Unloaded;
            asset->Data  = nullptr;

            // Remove load future.
            _loadFutures.erase(asset->Name);
        }
    }
}
