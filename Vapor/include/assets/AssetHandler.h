#pragma once



#include <iostream>
#include <map>
#include <set>
#include <filesystem>


#include "Asset.h"
#include "../utils/Singleton.h"
#include "../Types.h"

namespace fs = std::filesystem;

namespace vpr {

template<class AssetType> class AssetHandler: public Singleton<AssetHandler<AssetType>> {

    public:
        friend class Singleton<AssetHandler<AssetType>>;

    AssetHandler();

    AssetType* create(AssetTypeId id);

    AssetType* getAsset(std::string name);
    AssetType* getAsset(AssetTypeId id);

    bool isAvailable(std::string);
    bool isAvailable(AssetTypeId);

    bool isLoaded(AssetTypeId);
    bool isLoaded(std::string);

    AssetTypeId getId(std::string name);

    void deleteAsset(AssetTypeId id);
    void deleteAsset(AssetType *);

    void setBasePath(std::string);
    void setFileExtension(std::string);
    void loadAvailableAssets();
    bool addAvailableAsset(std::string);

    private:

    std::filesystem::path basePath;
    std::string fileExtension;

    std::map<AssetTypeId, AssetType*> assets;
    std::map<std::string, AssetTypeId> assetToId;
    std::set<AssetTypeId> availableAssets;
    std::set<AssetTypeId> loadedAssets;

    AssetTypeId currentId;

    AssetTypeId generateId();
    fs::path generatePath(std::string name);
};


template<class AssetType> 
AssetHandler<AssetType>::AssetHandler() {
    this->currentId = 1;
}

template<class AssetType>
AssetTypeId AssetHandler<AssetType>::generateId() {
    return currentId++;
}

template<class AssetType>
AssetType* AssetHandler<AssetType>::create(AssetTypeId id) {
    assert(isAvailable(id));

    AssetType* asset = (AssetType*)new AssetType();
    assets[id] = asset;

    return asset;
}

template<class AssetType>
void AssetHandler<AssetType>::deleteAsset(AssetTypeId id) {

    typename std::map<AssetTypeId, AssetType*>::iterator assetIter;
    
    assetIter = assets.find(id);

    if(assetIter == assets.end() || assetIter->second == nullptr) {
        std::cerr << "Trying to delete already deleted object\n";
        return;
    }
    
    delete assetIter->second;
    assets.erase(assetIter);
}


template<class AssetType>
void AssetHandler<AssetType>::deleteAsset(AssetType* asset) {
    if(asset != nullptr) {
        this->deleteAsset(asset->getId());
    }
}

template<class AssetType>
void AssetHandler<AssetType>::setBasePath(std::string basePath) {
    fs::path newPath = basePath;
    if(fs::exists(newPath)) {
        this->basePath =  basePath;
    } else {
        throw std::exception("unknown path ");
    }
}

template<class AssetType>
void AssetHandler<AssetType>::setFileExtension(std::string fileExtension) {
    this->fileExtension = fileExtension;
}

template<class AssetType>
void AssetHandler<AssetType>::loadAvailableAssets() {
    for(const auto& entry : fs::directory_iterator(basePath)) {
        if(entry.path().extension() == fileExtension) {
            std::string fileName = entry.path().stem().string();
            addAvailableAsset(fileName);
        }
    }
}

template<class AssetType>
bool AssetHandler<AssetType>::addAvailableAsset(std::string name) {
    if(assetToId.find(name) == assetToId.end()) {
        AssetTypeId newId = generateId();
        assetToId[name] = newId;
        availableAssets.insert(newId);
        return true;
    }
    return false;
}

template<class AssetType>
fs::path AssetHandler<AssetType>::generatePath(std::string assetName) {
    assert(!basePath.empty());
    assert(!fileExtension.empty());

    fs::path path = this->basePath + assetName;
    if(!fs::exists(path)) {
        throw std::exception("path " + path.string() + " does not exist");
    }
    return path;
}

template<class AssetType>
AssetType* AssetHandler<AssetType>::getAsset(std::string assetName) {
    assert(isAvailable(assetName));

    if(!isLoaded(assetName)) {
        AssetTypeId assetId = getId(assetName);
        auto path = generatePath(assetName);
        AssetType* newAsset = createAsset(assetId);
        newAsset->loadFromPath(path);
        loadedAssets.insert(assetId);
        return newAsset;
    } else {
        return (AssetType*)assets[getId(assetName)];
    }
}

template<class AssetType>
AssetType* AssetHandler<AssetType>::getAsset(AssetTypeId assetId) {
    assert(assets.find(assetId) == assets.end());
        
    return assets[assetId];
}

template<class AssetType>
AssetTypeId AssetHandler<AssetType>::getId(std::string name) {
    assert(isAvailable(name));
    return assetToId[name];
}
template<class AssetType>
bool AssetHandler<AssetType>::isAvailable(std::string name) {
    if(assetToId.find(name) != assetToId.end()) {
        return isAvailable(assetToId[name]);
    }
    return false;
}

template<class AssetType>
bool AssetHandler<AssetType>::isAvailable(AssetTypeId id) {
        return availableAssets.find(id) != availableAssets.end();
    return false;
}

template<class AssetType>
bool AssetHandler<AssetType>::isLoaded(AssetTypeId id) {
    return loadedAssets.find(id) != loadedAssets.end();
}

template<class AssetType>
bool AssetHandler<AssetType>::isLoaded(std::string name) {
    return isLoaded(getId(name));
}

}
