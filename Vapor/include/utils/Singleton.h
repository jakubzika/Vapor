#pragma once

template <class T> class Singleton
{
public:
  
  static
  T* get_instance()
  {
    if (!instance_)
      {
        instance_ = new T();
      }

    return instance_;
  }

  static
  void destroy_instance()
  {
    delete instance_;
    instance_ = nullptr;
  }

private:
  static T* instance_;
};

template <class T> T*  Singleton<T>::instance_ = nullptr;