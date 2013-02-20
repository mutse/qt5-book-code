if (args.length == 0)
    throw Error("No files specified on the command line");

for (var i = 0; i < args.length; ++i) {
    spreadsheet.clearData();
    if (!spreadsheet.addData(args[i], PumpSpreadsheet.Pump2000))
        throw Error("Error loading Pump 2000 data");

    var outFileName = args[i];
    if (outFileName.slice(-4) == ".p20")
        outFileName = outFileName.slice(0, -4);
    outFileName += ".gpx";

    if (!spreadsheet.saveData(outFileName, PumpSpreadsheet.GasPumpXml))
        throw Error("Error saving GasPumpXml data");

    print("Created " + outFileName + " from " + args[i]);
}
