#pragma once


class KODUtils {
public:
  template<typename T>
  static T* GetKODPlayerComponent(APawn* PlayerPawn) {
    if(!PlayerPawn) return nullptr;
    const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass()); 
    return Cast<T>(Component);
  }
};