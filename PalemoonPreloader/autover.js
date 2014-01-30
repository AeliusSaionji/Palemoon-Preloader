/////////////////////////////////////////////////////////////////////////////
// Automatic Version Resource Control
/////////////////////////////////////////////////////////////////////////////
// Copyright (C)2004 6XGate Incorporated
//
// This file is part of a AutoVersion
//
// AutoVersion is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// AutoVersion is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with AutoVersion; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
/////////////////////////////////////////////////////////////////////////////

// Objects
var FileSys, Args, FileObj;
// Counters
var i;
// Variables
var InFile, OutFile, BuildNumber;

// OpenTextFile constants
ForReading = 1; ForWriting = 2;
TristateFalse = 0;

// Initialize Objects and Variables
Args = WScript.Arguments;
FileSys = new ActiveXObject('Scripting.FileSystemObject');
BuildNumber = 0;

// Parse the command-line arguments
for (i = 0; i < Args.length; i++) {
	if (Args(i) == '-n') {
		if (i != Args.length - 1) InFile = Args(i + 1);
	} 
	if (Args(i) == '-o') {
		if (i != Args.length - 1) OutFile = Args(i + 1);
	}
}

// Echo the version information
WScript.Echo('AutoVer Script version 1.0 revision 10');
WScript.Echo('===============================================================================');
// Echo argument information
WScript.Echo('Input File: ' + InFile + '    Output File: ' + OutFile);

// Does the input file exist?
if (FileSys.FileExists(InFile)) {
	// Open the input file and get the build number
	FileObj = FileSys.OpenTextFile(InFile, ForReading, false, TristateFalse);
	BuildNumber = parseInt(FileObj.ReadLine());
	FileObj.Close();

	// Close and delete the file so it can be updated
	FileSys.DeleteFile(InFile, true);
} else {
	// Tell the user we are creating a new input file
	WScript.Echo('Warning: No input file, creating a new one.');
}

// Update and echo the build number
WScript.Echo('Currnet Build: ' + BuildNumber.toString());
BuildNumber++;
WScript.Echo('New Build:     ' + BuildNumber.toString());

// Create a new input files and write the new build number
FileObj = FileSys.OpenTextFile (InFile, ForWriting, true, TristateFalse);
FileObj.WriteLine(BuildNumber.toString());
FileObj.Close();

// Delete the output fileif
if (FileSys.FileExists(OutFile)) FileSys.DeleteFile(OutFile, true);

// Create the new outfile
FileObj = FileSys.OpenTextFile (OutFile, ForWriting, true, TristateFalse);
FileObj.WriteLine('// Automaticly generated file, do not edit directly');
FileObj.WriteBlankLines(1);
FileObj.WriteLine('#define BUILD_NUM ' + BuildNumber.toString());
FileObj.WriteLine('#define BUILD_STR "' + BuildNumber.toString() + '"');
