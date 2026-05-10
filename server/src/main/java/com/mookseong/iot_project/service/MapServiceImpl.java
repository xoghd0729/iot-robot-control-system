package com.mookseong.iot_project.service;

import com.mookseong.iot_project.data.Robot;
import com.mookseong.iot_project.repository.MapRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

@Service
@RequiredArgsConstructor
public class MapServiceImpl implements MapService {

  private final MapRepository repository;

  private static final int N = 5;
  private static final int PATHWAY_COLOR = 0;
  private static final int WALL_COLOR = 1;
  private static final int BLOCKED_COLOR = 2;
  private static final int PATH_COLOR = 3;
  private Integer[][] map;

  public boolean findMap(int x, int y) {
    if (x < 0 || y < 0 || x >= N || y >= N) {
      return false;
    } else if (map[x][y] != PATHWAY_COLOR) {
      return false;
    } else if (x == N - 1 && y == N - 1) {
      //출구의 경우 (배열의 끝 of 끝)
      map[x][y] = PATH_COLOR;
      return true;
    } else {
      map[x][y] = PATH_COLOR;
      if (findMap(x - 1, y) || findMap(x, y + 1) || findMap(x + 1, y) || findMap(x, y - 1)) {
        return true;
      }
      map[x][y] = BLOCKED_COLOR;
      return false;
    }
  }

  public String findDirections(Integer id) {
    map = repository.getMap();
    Robot robot = repository.getRobot(id);
    int x = robot.getX();
    int y = robot.getY();
    map[x][y] = 0;
    findMap(x, y);
    for (Integer[] ints : map) {
      for (int anInt : ints) {
        System.out.print(anInt + " ");
      }
      System.out.println("");
    }
    System.out.println("");
    if (x + 1 < map.length && map[x + 1][y] == 3) {
      repository.setMapData(x + 1, y, id);
      return "DOWN";
    } else if (y + 1 < map[0].length && map[x][y + 1] == 3) {
      repository.setMapData(x, y + 1, id);
      return "RIGHT";
    } else if (x - 1 >= 0 && map[x - 1][y] == 3) {
      repository.setMapData(x - 1, y, id);
      return "UP";
    } else if (y - 1 >= 0 && map[x][y - 1] == 3) {
      repository.setMapData(x, y - 1, id);
      return "LEFT";
    }
    return "STOP";
  }

  @Override
  public void setMapData(Integer x, Integer y, Integer id) {
    repository.setMapData(x, y, id);
  }

  @Override
  public Integer[][] getMap() {
    map = repository.getMap();
    Robot robot = repository.getRobot(1);
    int x = robot.getX();
    int y = robot.getY();
    map[x][y] = 4;
    return map;
  }


}
