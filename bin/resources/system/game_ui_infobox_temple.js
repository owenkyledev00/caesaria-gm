function OnShowTempleInfobox(location) {

}

function InfobboxWindow (rx,ry,rw,rh) {
  this.window = g_ui.addSimpleWindow(rx,ry,rw,rh)
}

game.ui.infobox.simple = function(rx,ry,rw,rh) {
  var ibox = new InfobboxWindow(rx,ry.rw,rh)
  ibox.title = "FONT_5"

  ibox.autoPosition = true
  ibox.blackFrame = ibox.addLabel(0, 0, 0, 0,)
  ibox.style = "blackFrame"
  /*{
    bgtype :
    font : "FONT_2"
    textAlign : [ "upperLeft", "upperLeft" ]
    text.offset : [ 50, 15 ]
  }*/

  lbTitle#Label :
  {
    geometry : [ 12, 12, "100%-12", "12+30" ]
    text : "##title##"
    font : "FONT_5"
    textAlign : [ "center", "center" ]
  }

  btnHelp#TexturedButton :
  {
    tooltip : "##infobox_tooltip_help##"
    geometry : [ 0, 0, 24, 24 ]
    normal : [ "paneling", 528 ]
    hovered : [ "paneling", 529 ]
    pressed : [ "paneling", 530 ]
    disabled : [ "paneling", 531 ]
  }

  layoutCallbacks#HLayout :
  {
    geometry : [ 32, "ph-40", "pw-32", "ph-16" ]
  }

  btnExit#TexturedButton :
  {
    tooltip : "##infobox_tooltip_exit##"
    geometry : [ 0, 0, 24, 24 ]
    normal : [ "paneling", 532 ]
    hovered : [ "paneling", 533 ]
    pressed : [ "paneling", 534 ]
    disabled : [ "paneling", 535 ]
  }

  lbText#Label :
  {
    geometry : [ 32, 64, "pw-20", 128 ]
    multiline : true
    font : "FONT_2"
    multiline : true
  }
}

game.ui.infobox.aboutConstruction = function() {
  var btnNext#PushButton : {
    id : 190 /* 0xbe */
    geometry : [ "pw-36", 12, "pw-12", 36 ]
    text : ">"
    bgtype : "whiteBorderUp"
    tooltip : "##infobox_construction_comma_tip##"
  }

  btnPrev#PushButton : {
    id : 188 /* 0xbe */
    geometry : [ "pw-60", 12, "pw-36", 36 ]
    text : "<"
    bgtype : "whiteBorderUp"
    tooltip : "##infobox_construction_comma_tip##"
  }
}

game.ui.infobox.aboutTemple = function(location) {

}
