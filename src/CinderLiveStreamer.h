/*
 Copyright (c) 2014, Vladimir Gusev - All rights reserved.
 This code is intended for use with the Cinder C++ library: http://libcinder.org
 
 This file is part of Cinder-LiveStream block.
 
 Cinder-LiveStream is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 Cinder-LiveStream is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with Cinder-LiveStream.  If not, see <http://www.gnu.org/licenses/>.
 */




#include "cinder/app/App.h"

class CinderLiveStreamer {
  public:
	CinderLiveStreamer();
    static std::string getStreamUrl(std::string);
};

std::string CinderLiveStreamer::getStreamUrl(const std::string pageUrl) //_link is the complete url, just like above.
{
    std::string lvstrmr = "/usr/local/bin/livestreamer";
    std::string cmd = lvstrmr + " " + pageUrl + " best --stream-url";
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    result.erase(remove(result.begin(), result.end(), '\n'), result.end());
    std::string dlStream = result;
    
    return ( dlStream);
}
