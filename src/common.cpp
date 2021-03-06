/******************************************************************************
 *
 * CoreWall / Corelyzer - An Initial Core Description Tool
 * Copyright (C) 2004, 2005 Arun Gangadhar Gudur Rao, Julian Yu-Chung Chen,
 * Sangyoon Lee, Electronic Visualization Laboratory, University of Illinois
 * at Chicago
 *
 * This software is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either Version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser Public License along
 * with this software; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Questions or comments about CoreWall should be directed to
 * cavern@evl.uic.edu
 *
 *****************************************************************************/

#include "common.h"

static bool DEBUG_MODE = false;

void setDebug(bool b)
{
    DEBUG_MODE = b;
}

bool getDebug()
{
    return DEBUG_MODE;    
}

#if defined(__APPLE__) && !defined(JAVA_BINDING)
char* getFilePathInBundle(const char* fileName, const char* fileType)
{
	CFBundleRef frameworkBundle = CFBundleGetBundleWithIdentifier(CFSTR("org.corewall.LODRender"));
	CFStringEncoding encoding = kCFStringEncodingASCII;
	
	if(frameworkBundle != NULL)
	{
		CFStringRef cfFileName = CFStringCreateWithCString(NULL, fileName, encoding);
		CFStringRef cfFileType = CFStringCreateWithCString(NULL, fileType, encoding);
		
		CFURLRef fileURL = CFBundleCopyResourceURL(frameworkBundle,
												   cfFileName, cfFileType,
												   NULL);
		CFRelease(cfFileName);
		CFRelease(cfFileType);
		
		if(fileURL != NULL)
		{
			CFStringRef pathString = CFURLCopyFileSystemPath(fileURL, kCFURLPOSIXPathStyle);
			
			const int kBufferSize = 256;
			char* filePath = (char *) malloc(kBufferSize);
			
			Boolean b = CFStringGetCString(pathString, filePath, kBufferSize, encoding);
			CFRelease(pathString);
			
			if(b)
			{
				return filePath;
			}
		}
	}
	
	return NULL;
}
#endif
