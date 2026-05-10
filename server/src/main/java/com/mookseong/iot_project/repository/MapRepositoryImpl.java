package com.mookseong.iot_project.repository;

import com.mookseong.iot_project.data.Robot;
import java.util.HashMap;
import java.util.Map;
import org.springframework.stereotype.Repository;

@Repository
public class MapRepositoryImpl implements MapRepository {

  private static final Map<Integer, Robot> robotMap = new HashMap<>();
  private static final Integer[][] map = {
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
  };
  @Override
  public Integer[][] getMap() {
    Integer[][] clonedMap = new Integer[map.length][map[0].length];
    for (int i = 0; i < map.length; i++) {
      System.arraycopy(map[i], 0, clonedMap[i], 0, map[0].length);
    }
    return clonedMap;
  }

  @Override
  public void setMapData(Integer x, Integer y, Integer id) {
    if (robotMap.containsKey(id)) {
      Robot robot = robotMap.get(id);
      int _x = robot.getX();
      int _y = robot.getY();
      map[_x][_y] = 0;
    }
    robotMap.put(id, new Robot(x, y));
    map[x][y] = 1;
  }

  public Robot getRobot(Integer id){
    return robotMap.get(id);
  }



}
