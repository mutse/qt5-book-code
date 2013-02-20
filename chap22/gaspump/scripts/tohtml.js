if (args.length == 0)
    throw Error("No files specified on the command line");

print("<table border=\"1\" width=\"100%\">");
for (var i = 0; i < args.length; ++i) {
    spreadsheet.clearData();
    if (!spreadsheet.addData(args[i], PumpSpreadsheet.Pump2000))
        throw Error("Error loading Pump 2000 data");

    print("<th colspan=\"" + spreadsheet.columnCount + "\">"
          + args[i] + "</th>");
    for (var row = 0; row < spreadsheet.rowCount; ++row) {
        print("<tr>");
        for (var column = 0; column < spreadsheet.columnCount;
             ++column) {
            print("<td>" + spreadsheet.text(row, column) + "</td>");
        }
        print("</tr>");
    }
}
print("</table>");
