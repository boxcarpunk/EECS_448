/* Side Navigation animation from: https://www.w3schools.com/howto/howto_js_sidenav.asp */

function openNav() {
    $("#sideNav").width("250px");
    document.getElementById("main").style.marginLeft = "250px";
//    $("#main").style.marginLeft = "250";
    $("#openBtn").fadeOut();
    $("#openBtn-wht").fadeOut();
}

/* Set the width of the side navigation to 0 and the left margin of the page content to 0, and the background color of body to white */
function closeNav() {
    $("#sideNav").width("0");
    document.getElementById("main").style.marginLeft = "0";
    $("#openBtn").fadeIn();
    $("#openBtn-wht").fadeIn();
}
