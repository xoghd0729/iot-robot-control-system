package com.mookseong.iot_project.repository;

import com.mookseong.iot_project.data.Robot;

public interface MapRepository {

  void setMapData(Integer x, Integer y, Integer id);

  Robot getRobot(Integer id);
  Integer[][] getMap();
}
