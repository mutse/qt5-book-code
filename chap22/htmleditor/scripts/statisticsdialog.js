var obj = new Object;

obj.text = "&Statistics...";

obj.run = function() {
    var text = this.textEdit.plainText;
    this.dialog.frame.charCountLineEdit.text = text.length;
    this.dialog.frame.wordCountLineEdit.text = this.wordCount(text);
    this.dialog.frame.lineCountLineEdit.text = this.lineCount(text);
    this.dialog.exec();
};

obj.wordCount = function(text) {
    var regExp = new RegExp("\\w+", "g");
    var count = 0;
    while (regExp.exec(text))
        ++count;
    return count;
};

obj.lineCount = function(text) {
    var count = 0;
    var pos = 0;
    while ((pos = text.indexOf("\n", pos)) != -1) {
        ++count;
        ++pos;
    }
    return count + 1;
};

return obj;
