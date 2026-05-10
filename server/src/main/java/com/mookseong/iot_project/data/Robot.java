package com.mookseong.iot_project.data;

import lombok.Builder;
import lombok.Data;
import lombok.Getter;
import org.springframework.web.bind.annotation.GetMapping;

public class Robot {

  private int x;
  private int y;

  public Robot(int x, int y) {
    this.x = x;
    this.y = y;
  }

  public int getX() {
    return x;
  }

  public int getY() {
    return y;
  }
}
