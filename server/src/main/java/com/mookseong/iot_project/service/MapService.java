package com.mookseong.iot_project.service;

public interface MapService {
  String findDirections(Integer id);
  void setMapData(Integer x, Integer y, Integer id);

  Integer[][] getMap();
}
