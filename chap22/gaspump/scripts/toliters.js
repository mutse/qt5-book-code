const LitersPerGallon = 3.785411784;

if (args.length == 0)
    throw Error("No files specified on the command line");

for (var i = 0; i < args.length; ++i) {
    spreadsheet.clearData();
    if (!spreadsheet.addData(args[i], PumpSpreadsheet.Pump2000))
        throw Error("Error loading Pump 2000 data");

    spreadsheet.convertUnits(LitersPerGallon);
    if (!spreadsheet.saveData(args[i], PumpSpreadsheet.Pump2000))
        throw Error("Error saving Pump 2000 data");

    print("Converted gallons to liters in " + args[i]);
}
