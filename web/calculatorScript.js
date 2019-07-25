function calculatorBtnPress(value) {
    //get DOM element in the calculator with id=display, [0] to ge obj
    let display = $("#calculator #display")[0];
    //depending on the input
    //save input value to the display text
    switch (value) {
    case '0': display.value += '0';
        break;
    case '1': display.value += '1';
        break;
    case '2': display.value += '2';
        break;
    case '3': display.value += '3';
        break;
    case '4': display.value += '4';
        break;
    case '5': display.value += '5';
        break;
    case '6': display.value += '6';
        break;
    case '7': display.value += '7';
        break;
    case '8': display.value += '8';
        break;
    case '9': display.value += '9';
        break;
    case '+': display.value += '+';
        break;
    case '-': display.value += '-';
        break;
    case '*': display.value +='*';
        break;
    case '/': display.value += '/';
        break;
    case 'c': display.value = '';
        break;
    //using js func eval, calculating the expression, after what show the result on the display
    case '=': display.value = eval(display.value);
        break;
    }
}