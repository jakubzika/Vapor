#pragma once



#include <iostream>
#include <map>

#include "Asset.h"
#include "../utils/Singleton.h"
#include "../Types.h"

namespace vpr {

template<class AssetType> class AssetHandler: public Singleton<AssetHandler<AssetType>> {

    public:
        friend class Singleton<AssetHandler<AssetType>>;


    AssetHandler();
    // virtual ~AssetHandler();

    AssetType* loadFromFile(const std::string &path);
    // AssetType* loadFromMemory(void * data, std::size_t size);

    AssetType* loadFromFile(AssetTypeId id, const std::string &path);
    // AssetType* loadFromMemory(AssetTypeId id, void * data, std::size_t size);

    AssetType* getAsset();
    AssetType* addAsset(AssetTypeId id);

    void deleteAsset(AssetTypeId id);
    void deleteAsset(AssetType *);

    private:

    std::map<AssetTypeId, AssetType*> assets;
    AssetTypeId currentId;

    AssetTypeId generateId();
};


template<class AssetType> 
AssetHandler<AssetType>::AssetHandler() {
    this->currentId = 1;
}


template<class AssetType> 
AssetType* AssetHandler<AssetType>::loadFromFile(const std::string &path) {
    return this->loadFromFile(this->generateId(),path);
}

template<class AssetType>
AssetType* AssetHandler<AssetType>::loadFromFile(AssetTypeId id, const std::string &path) { 
    AssetType* asset = this->addAsset(id);
    std::cout<<"load asset from file\n";
    asset->loadFromPath(path);

    return (AssetType*)asset;
}

template<class AssetType>
AssetTypeId AssetHandler<AssetType>::generateId() {
    return currentId++;
}

template<class AssetType>
AssetType* AssetHandler<AssetType>::addAsset(AssetTypeId id) {
    AssetType* asset = nullptr;

    typename std::map<AssetTypeId, AssetType*>::iterator assetIter;
    assetIter = assets.find(id);

    if(assetIter != assets.end()){
        std::cerr << "Asset with given id already exists\n";
        return nullptr;
    }

    asset = (AssetType*)new AssetType();
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


}
