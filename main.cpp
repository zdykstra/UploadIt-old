/*
 * Copyright 2018. All rights reserved.
 * Distributed under the terms of the MIT license.
 *
 * Authors:
 *	Humdinger, humdingerb@gmail.com
 *	Werner Freytag, freytag@gmx.de
 *
 * Modified code from CopyNameToClipboard
 */
 
#include <stdio.h>
#include <stdlib.h>

#include <Catalog.h>
#include <Clipboard.h>
#include <Entry.h>
#include <Path.h>
#include <String.h>

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "Add-On"


extern "C" void
process_refs(entry_ref directoryRef, BMessage* msg, void*)
{
	BPath path;
	entry_ref file_ref;

	if (msg->FindRef("refs", 0, &file_ref) == B_NO_ERROR) {
		BEntry(&file_ref).GetPath(&path);
		BString command(
			"stat=$(curl -m 2 -s -I http://google.com | grep HTTP/1 | awk {'print $2'}) ; "
			"if [ -z  \"$stat\" ] ; then "	// network up in general?
				"clipboard -c \"%ERROR%\" ; "
			"else "
				"curl -F'file=@'%FILENAME% https://0x0.st | clipboard -i ; "
			"fi ; "
			"exit");
		command.ReplaceAll("%ERROR%",
			B_TRANSLATE("Online upload service not available"));
		command.ReplaceAll("%FILENAME%", path.Path());
		system(command.String());
	}
}


int
main(int, char**)
{
	fprintf(stderr, B_TRANSLATE("UploadIt can only be used as a Tracker add-on.\n"));
	return -1; 
}