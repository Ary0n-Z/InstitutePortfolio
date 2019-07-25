//checks form for empty fields
(function ($) {
    $(function () {
        //Find all forms which has requaire-form class
        $('.requaire-form').each(function () {
            var form = $(this);
            //Find submit button in the form
            var btn = form.find('.btn-submit');
            //add class empty_field to all required fields(rfield)
            //from the start fields are empty
            form.find('.rfield').addClass('empty-field');

            //check input function define
            function checkInput() {
                //for each required field
                form.find('.rfield').each(
                    //call function
                    function () {
                        
                        if ($(this).val() != '') {
                            //if value in the current field is not empty, remove 'empty_field' class from it
                            $(this).removeClass('empty-field');
                        } else {
                            //give to the field 'empty_field' class
                            $(this).addClass('empty-field');
                        }
                    }
                );
            }
       

            //Light up required fields in which value are empty
            function lightEmpty() {
                //make all empty fields border red
                form.find('.empty-field').css({ 'border-color': '#d8512d' });
                //call func after 0.5s
                setTimeout(function () {
                    // func will remove style for all empty fields -> red border will be removed
                    form.find('.empty-field').removeAttr('style');
                }, 500);
            }

            //like a timer, call func evry 0.5s
            setInterval(function () {
                //Checking for empty fields
                checkInput();
                //getting number of empty fields
                var sizeEmpty = form.find('.empty-field').length;
                if (sizeEmpty > 0) {
                    //if we have min 1 empty field, give button class btn-disabled
                    if (!btn.hasClass('btn-disabled')) {
                        btn.addClass('btn-disabled');
                    } 
                } else {
                    //else, remove the class
                    btn.removeClass('btn-disabled')
                }
            }, 500);

            //depending on btn-disabled class,
            btn.click(function () {
                //if btn can be pressed. P.S. Only when required fields are not empty
                if ($(this).hasClass('btn-disabled')) {
                    //make fields border red colored, to warn user
                    lightEmpty();
                } 
                //call form submit, to check for patterns
                form.submit();
            });
        });
    });

})(jQuery);



function validateSecret() {
    let secret = $('#secret')[0];
    let secretValue = secret.value;
    let upper = /[A-Z]/.exec(secretValue);
    let lower = /[a-z]/.exec(secretValue);
    let digit = /[0-9]/.exec(secretValue);
    let special = /[!@#$%^&*_.]/.exec(secretValue);
    if (secretValue.length < 8) {
        secret.title = "Minimul secret msg length is 8!";
        return false;
    }
    if (upper == null) {
        secret.title = "No uppercase in the secret!";
        return false;
    }
    if (lower == null) {
        secret.title = "No lowercase in the secret!";
        return false;
    }
    if (digit == null) {
        secret.title = "No digits in the secret!";
        return false;
    }
    if (special == null) {
        secret.title = "No special in the secret!";
        return false;
    }
    return true;
}
function confrmcb(isSelected) {
    var btn = $('.btn-submit')[0];
    btn.disabled = !isSelected;
}