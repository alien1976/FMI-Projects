"use strict";

var flag = false;
$(document).ready(function () {
   $(".copy").click(function(){
    if ($("#txtarea").val()) {
        $("#txtarea").select();
        if(document.execCommand('copy')){
            console.log('copied');
        }
        window.alert("Code copied in buffer!");    
    }else{
        window.alert("Nothing copied! Text area is empty!");
    }
});
   $(".handler").each(function (index) {
    $(this).on("click", function (event) {
        event.stopPropagation();
        var element = $(this);
        var type = element.attr('id');
        if (flag == false) {
            flag = true;
            checkType(type);
        }
    });
});

   $('.close').on('click', function () {
    $(".modal-backdrop").css('display', 'none');
    $(".form-inline").css('display', 'none');
    $("#preview").css('display', 'none');
    $("body").removeClass("dialogIsOpen");
    flag = false;
});

   $(document).mouseup(function (e) {
    var container = $(".form-inline");
    var colorPicker = $("#colorpicker");
    if (!colorPicker.is(e.target) && colorPicker.has(e.target).length === 0) {
        if (!container.is(e.target) && container.has(e.target).length === 0) {
            container.hide();
            colorPicker.hide();
            $("body").removeClass("dialogIsOpen");
        }
    }

});

   $(document).keyup(function(e){
    if(e.keyCode == 27){
        $(".modal-backdrop").css('display', 'none');
        $(".form-inline").css('display', 'none');
        $("#preview").css('display', 'none');
        $("body").removeClass("dialogIsOpen");
        flag = false;
    }
})

   function checkType(type) {
    $("#txtarea").empty();
    var nameSelector = "<label>Name Selector</label> &nbsp;<input type='text' class='form-control nameSelector'></input></br>";
    var selector = "<label>Selector</label> &nbsp;<select name='selector' class='form-control selector'>"
    + "<option value='id'>id</option>"
    + "<option value='class'>class</option>"
    + "<option value='element'>element</option>"
    + "<option value='all elements'>all elements</option></select></br>";
    switch (type) {
        case 'Radius':
        radiusBorder(" Border " + type + " ", nameSelector, selector);
        type = "";
        flag = false;
        break;
        case 'Shadow':
        ShadowBox(" " + type + " Box ", nameSelector, selector);
        flag = false;
        break;
        case 'Text-shadow':
        TextShadow(" " + type + " ", nameSelector, selector);
        flag = false;
        break;
        case 'Rgba':
        RGB(" " + type + " ", nameSelector, selector);
        flag = false;
        break;
        case 'Font-face':
        FontFamily(" " + type + " ", nameSelector, selector);
        flag = false;
        break;
        case 'Multiple-column':
        MultipleColumns(" " + type + " ", nameSelector, selector);
        flag = false;
        break;
        case 'Box-sizing':
        BoxSizing(" " + type + " ", nameSelector, selector);
        flag = false;
        break;
        case 'Box-resizing':
        BoxResizing(" " + type + " ", nameSelector, selector);
        flag = false;
        break;
        case 'Outline':
        Outline(" " + type + " ", nameSelector, selector);
        flag = false;
        break;
        case 'Transition':
        Transition(" " + type + " ", nameSelector, selector);
        flag = false;
        break;
        case 'Transform':
        Transform(" " + type + " ", nameSelector, selector);
        flag = false;
        break;
        case 'Flexbox':
        Flex(" " + type + " ", nameSelector, selector);
        flag = false;
        break;
        default:
        console.log("error");
        flag = false;
    }
}
    //tezi dve funkcii sa za otdelnite neshta

});