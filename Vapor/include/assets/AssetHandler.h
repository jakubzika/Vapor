/**
 * \file       AssetHandler.h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      description
 *
 *  Handler for handling
 *
*/

#pragma once



#include <iostream>
#include <map>
#include <set>
#include <filesystem>


#include "Asset.h"
#include "../utils/Singleton.h"
#include "../Types.h"


namespace vpr {

/**
 * @brief generic asset handler for loading assets from file system
 * 
 */
template<class AssetType> class AssetHandler: public Singleton<AssetHandler<AssetType>> {

    public:
        friend class Singleton<AssetHandler<AssetType>>;

    AssetHandler();

    /**
     * @brief Creates empty asset with specified id
     * 
     * @param id 
     * @return AssetType* 
     */
    AssetType* create(AssetTypeId id);
    
    /**
     * @brief Get the Asset object by name
     * 
     * @param name asset name
     * @return AssetType* 
     */
    AssetType* getAsset(string name);

    /**
     * @brief Get the Asset object by id
     * 
     * @param id 
     * @return AssetType* 
     */
    AssetType* getAsset(AssetTypeId id);

    /**
     * @brief Checks if given asset name is available
     * @param name asset name
     * @return true 
     * @return false 
     */
    bool isAvailable(string name);

    /**
     * @brief Checks if given asset id is available
     * @param id asset id
     * @return true 
     * @return false 
     */
    bool isAvailable(AssetTypeId id);

    /**
     * @brief Checks if asset has been loaded or is yet waiting to be loaded
     * @param id asset id
     * @return true 
     * @return false 
     */
    bool isLoaded(AssetTypeId id);

    /**
     * @brief Checks if asset has been loaded or is yet waiting to be loaded
     * @param name asset name
     * @return true 
     * @return false 
     */
    bool isLoaded(string name);

    /**
     * @brief Get the Id of asset from asset name
     * 
     * @param name 
     * @return AssetTypeId 
     */
    AssetTypeId getId(string name);

    /**
     * @brief Get the name of asset from asset Id
     * 
     * @param id 
     * @return string 
     */
    string getName(AssetTypeId id);

    /**
     * @brief Deletes specified asset 
     * 
     * @param id 
     */
    void deleteAsset(AssetTypeId id);

    /**
     * @brief Deletes specified asset
     * 
     * @param asset 
     */
    void deleteAsset(AssetType* asset);

    /**
     * @brief Set the Base Path to the directory which will the AssetHandler scan for available assets
     * 
     */
    void setBasePath(string);

    /**
     * @brief Set the File Extension of the asset file for which the handler will look for
     * 
     */
    void setFileExtension(string);

    /**
     * @brief Scand base path folder for folders with files with set exteinson
     * 
     */
    void loadAvailableAssets();

    /**
     * @brief Adds asset
     * 
     * @return true 
     * @return false 
     */
    bool addAvailableAsset(string);

    /**
     * @brief Add asset manually which is not present in resource folders
     * 
     * @param asset 
     * @param name 
     * @return AssetTypeId 
     */
    AssetTypeId addAssetManually(AssetType* asset,string name);

    private:

    std::filesystem::path basePath;
    string fileExtension;

    std::map<AssetTypeId, AssetType*> assets;
    std::map<string, AssetTypeId> assetToId;
    std::set<AssetTypeId> availableAssets;
    std::set<AssetTypeId> loadedAssets;

    AssetTypeId currentId;

    AssetTypeId generateId();
    fs::path generatePath(string name);
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
    asset->setId(id);

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
void AssetHandler<AssetType>::setBasePath(string basePath) {
    fs::path newPath = basePath;
    if(fs::exists(newPath)) {
        this->basePath =  basePath;
    } else {
        std::cout << "Unknown path " << newPath.string() << std::endl;
        throw "unknown path " + newPath.string();
    }
}

template<class AssetType>
void AssetHandler<AssetType>::setFileExtension(string fileExtension) {
    this->fileExtension = fileExtension;
}

template<class AssetType>
void AssetHandler<AssetType>::loadAvailableAssets() {
    for(const auto& entry : fs::directory_iterator(basePath)) {
        if(fs::is_directory(entry.path()))
        if(fs::is_directory(entry.path())) { 
            string directoryName = entry.path().stem().string();
            // fs::path fileName = directoryName + "." + fileExtension;
            fs::path filePath = entry.path() / ( directoryName + fileExtension);
            if(fs::exists(filePath)) {
                std::cout << "Adding asset " << directoryName << " at " << filePath << std::endl; 
                addAvailableAsset(directoryName);
            } else {
                std::cout << "Asset path for" << directoryName << " at " << filePath << " does not exist " << std::endl; 
            }
        }
    }
}

template<class AssetType>
bool AssetHandler<AssetType>::addAvailableAsset(string name) {
    if(assetToId.find(name) == assetToId.end()) {
        AssetTypeId newId = generateId();
        assetToId[name] = newId;
        availableAssets.insert(newId);
        return true;
    }
    return false;
}

template<class AssetType>
fs::path AssetHandler<AssetType>::generatePath(string assetName) {
    assert(!basePath.empty());
    assert(!fileExtension.empty());

    fs::path path = (basePath / assetName) /  (assetName + fileExtension);
    if(!fs::exists(path)) {
        std::cout << "Path " << path.string() << " does not exist" << std::endl;
        throw "path " + path.string() + " does not exist";
    }
    return path;
}

template<class AssetType>
AssetType* AssetHandler<AssetType>::getAsset(string assetName) {
    assert(isAvailable(assetName));

    if(!isLoaded(assetName)) {
        AssetTypeId assetId = getId(assetName);
        auto path = generatePath(assetName);
        AssetType* newAsset = create(assetId);
        newAsset->load(path.string());
        loadedAssets.insert(assetId);
        return newAsset;
    } else {
        return (AssetType*)assets[getId(assetName)];
    }
}

template<class AssetType>
AssetType* AssetHandler<AssetType>::getAsset(AssetTypeId assetId) {
    return this->getAsset(this->getName(assetId));
}

template<class AssetType>
AssetTypeId AssetHandler<AssetType>::getId(string name) {
    if(!isAvailable(name)) {
        std::cout << "Asset " << name << " does not exist" << std::endl;
        throw "Asset " + name + " does not exist";
    }
    return assetToId[name];
}

template<class AssetType>
string AssetHandler<AssetType>::getName(AssetTypeId id) {
    for(auto it = assetToId.begin();  it != assetToId.end(); ++it) {
        if(it->second == id) return it->first;
    }
    return "";
}

template<class AssetType>
bool AssetHandler<AssetType>::isAvailable(string name) {
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
bool AssetHandler<AssetType>::isLoaded(string name) {
    return isLoaded(getId(name));
}


template<class AssetType>
AssetTypeId AssetHandler<AssetType>::addAssetManually(AssetType* asset, string name) {
    assert(assetToId.find(name) == assetToId.end());

    AssetTypeId newId = generateId();

    assetToId[name] = newId;
    availableAssets.insert(newId);
    loadedAssets.insert(newId);
    assets[newId] = asset;

    asset->setId(newId);

    return newId;
}

}
