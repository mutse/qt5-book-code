var obj = new Object;

obj.initialized = false;

obj.text = "&Reformat...";

obj.run = function() {
    if (!this.initialized) {
        this.dialog.applyButton.clicked.connect(this, this.apply);
        this.dialog.closeButton.clicked.connect(this, this.dialog.close);
        this.initialized = true;
    }
    this.dialog.show();
};

obj.apply = function() {
    var text = this.textEdit.plainText;

    this.textEdit.readOnly = true;
    this.dialog.applyButton.enabled = false;

    if (this.dialog.indentGroupBox.checked) {
        var size = this.dialog.indentGroupBox.indentSizeSpinBox.value;
        text = this.reindented(text, size);
    }
    if (this.dialog.wrapGroupBox.checked) {
        var margin = this.dialog.wrapGroupBox.wrapMarginSpinBox.value;
        text = this.wrapped(text, margin);
    }
    if (this.dialog.caseGroupBox.checked) {
        var lowercase = this.dialog.caseGroupBox.lowercaseRadio.checked;
        text = this.fixedTagCase(text, lowercase);
    }

    this.textEdit.plainText = text;
    this.textEdit.readOnly = false;
    this.dialog.applyButton.enabled = true;
};

obj.reindented = function(text, size) {
    var result = "";
    var depth = 0;
    var i = 0;

    while (i < text.length) {
        var line = "";
        var lineDepth = depth;

        while (i < text.length
               && (text.charAt(i) == " " || text.charAt(i) == "\t"))
            ++i;

        while (i < text.length && text.charAt(i) != "\n") {
            if (text.charAt(i) == "<") {
                var closing = (text.substring(i, i + 2) == "</");
                var openQuote;

                while (i < text.length && text.charAt(i) != ">") {
                    if (text.charAt(i) == "'"
                            || text.charAt(i) == "\"") {
                        openQuote = text.charAt(i++);
                        line += openQuote;
                        while (i < text.length
                               && text.charAt(i) != openQuote)
                            line += text.charAt(i++);
                    }
                    if (i < text.length)
                        line += text.charAt(i++);
                }

                var standAlone = (text.substring(i - 1, i + 1) == "/>");
                if (closing) {
                    --depth;
                } else if (!standAlone) {
                    ++depth;
                }
            } else {
                line += text.charAt(i++);
            }
        }
        line += "\n";
        ++i;

        if (line.substring(0, 2) == "</")
            --lineDepth;
        for (var j = 0; j < size * lineDepth; ++j)
            result += " ";
        result += line;

    }
    return result;
};

obj.wrapped = function(text, margin) {
    const TAB_SIZE = 8;
    var result = "";
    var lastSpace;
    var column = 0;
    var i = 0;

    while (i < text.length) {
        if (text.charAt(i) == "\n") {
            column = 0;
        } else if (text.charAt(i) == " ") {
            lastSpace = i;
            ++column;
        } else if (text.charAt(i) == "\t") {
            column = (column + TAB_SIZE - 1) / TAB_SIZE * TAB_SIZE;
        } else {
            if (column >= margin && lastSpace != undefined) {
                result = result.substring(0, lastSpace);
                result += "\n";
                column = 0;
                i = lastSpace + 1;
                lastSpace = undefined;
            }
            ++column;
        }
        result += text.charAt(i++);
    }
    return result;
};

obj.fixedTagCase = function(text, lowercase) {
    var result = "";
    var i = 0;
    while (i < text.length) {
        if (text.charAt(i) == "<") {
            var openQuote;
            while (i < text.length && text.charAt(i) != ">") {
                if (text.charAt(i) == "'" || text.charAt(i) == "\"") {
                    openQuote = text.charAt(i);
                    result += text.charAt(i++);
                    while (i < text.length
                           && text.charAt(i) != openQuote)
                        result += text.charAt(i++);
                    result += text.charAt(i++);
                } else {
                    if (lowercase) {
                        result += text.charAt(i++).toLowerCase();
                    } else {
                        result += text.charAt(i++).toUpperCase();
                    }
                }
            }
        } else {
            result += text.charAt(i++);
        }
    }
    return result;
};

return obj;
