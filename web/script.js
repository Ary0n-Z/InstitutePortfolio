//init float navigation menu
function navFloatMenu() {
    //search for floating menus
    let menu = $(".nav-float-menu");
    //float buttons in menu
    let button = menu.find('.nav-btn');
    //all links in it
    let links = menu.find('.nav-list-link');
    //and overlay, that lay in front of the page content
    let overlay = menu.find('.nav-overlay');

    //nav menu can opens when float btn pressed, and closes when link, close btn or overlay pressed
    function toggleMenu() {
        //For this purpose i use toggleClass func, that will add class if it is not defined and vice-versa
        menu.toggleClass('nav-float-menu-active');
        //avoid overflow of the content, when navigation is active
        if (menu.hasClass('nav-float-menu-active')) {
            $('body').css('overflow', 'hidden');
        } else {
            $('body').css('overflow', 'visible');
        }
    }

    button.on('click', (e) => {
        e.preventDefault();//disable default btn action
        //and make our, that toggles menu
        toggleMenu();
    })
    //the same with links and overlay
    links.on('click', () => { toggleMenu(); });
    overlay.on('click', () => { toggleMenu(); });

};

//binding clock time to the user time
(function ($) {
    //when page will be loaded
    $(document).ready(function () {
        //get clocks
        const svg = $('svg')[0];
        //and current time
        const currentTime = new Date();
        //and assigne current time to the css variables forv inner calculating
        svg.style.setProperty('--start-seconds', currentTime.getSeconds());
        svg.style.setProperty('--start-minutes', currentTime.getMinutes());
        svg.style.setProperty('--start-hours', currentTime.getHours() % 12);
    })
})(jQuery)