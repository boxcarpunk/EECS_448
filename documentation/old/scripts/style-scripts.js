/* Side Navigation, source in documentaion.txt under "Side Navigation" */

function openNav() {
  $("#sideNav").width("250px");
//    document.getElementById("main").style.marginLeft = "250px"; //moves page over to fit with sideNav, not working correctly...
  $("#openBtn").fadeOut();
  $("#openBtn-wht").fadeOut();
}

function closeNav() {
  $("#sideNav").width("0");
//    document.getElementById("main").style.marginLeft = "0"; //moves page over to fit with sideNav, not working correctly...
  $("#openBtn").fadeIn();
  $("#openBtn-wht").fadeIn();
}
