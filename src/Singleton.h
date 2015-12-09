#ifndef _Singleton_h_
#define _Singleton_h_

namespace JonTelldus {

  template<class TBase, int T = 0>
  class Singleton : public TBase 
  {
    private:
     static Singleton<TBase, T> instance;
    protected:
      Singleton() {}
    public:
      static TBase& getInstance();
  };

  template<class TBase, int T>
  Singleton<TBase, T> Singleton<TBase, T>::instance = Singleton<TBase, T>();

  template<class TBase, int T>
  TBase& Singleton<TBase, T>::getInstance() {
    return Singleton<TBase, T>::instance;
  }

}


#endif
