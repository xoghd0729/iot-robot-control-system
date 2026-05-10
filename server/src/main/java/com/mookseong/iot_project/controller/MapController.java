package com.mookseong.iot_project.controller;

import com.mookseong.iot_project.service.MapService;
import java.util.Arrays;
import lombok.RequiredArgsConstructor;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequiredArgsConstructor
public class MapController {

  private final MapService service;

  @GetMapping("/robot")
  public String setMapData(
      @RequestParam Integer x,
      @RequestParam Integer y,
      @RequestParam Integer id
  ) {
    service.setMapData(x, y, id);
    return "DONE";
  }

  @GetMapping("/find")
  public String findDirections(
      @RequestParam Integer id
  ) {
    return service.findDirections(id);
  }


  @GetMapping("/map")
  public String getMap() {
    return Arrays.deepToString(service.getMap());
  }

}
