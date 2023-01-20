#ifndef GAME_VERSIONS_NSMBW_H
#define GAME_VERSIONS_NSMBW_H

// MIT License

// Copyright (c) 2022 RoadrunnerWMC

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


// This header defines additional preprocessor symbols for NSMBW mods
// specifically. Different games would need different logic depending on
// their release history. The symbols exposed by this header are for
// convenience and are not considered part of the build system's API.


// First, define constants for every game version, region, and revision.

// The revision values are sorted in chronological order, so it's safe
// to do comparisons such as "GAME_REVISION < GAME_REVISION_K".

#define GAME_VERSION_DYNAMIC 1
#define GAME_VERSION_P1 2
#define GAME_VERSION_E1 3
#define GAME_VERSION_J1 4
#define GAME_VERSION_P2 5
#define GAME_VERSION_E2 6
#define GAME_VERSION_J2 7
#define GAME_VERSION_P3 8
#define GAME_VERSION_J3 9
#define GAME_VERSION_K 10
#define GAME_VERSION_W 11
#define GAME_VERSION_C 12

#define GAME_REGION_P 1
#define GAME_REGION_E 2
#define GAME_REGION_J 3
#define GAME_REGION_K 4
#define GAME_REGION_W 5
#define GAME_REGION_C 6

#define GAME_REVISION_V1 1
#define GAME_REVISION_V2 2
#define GAME_REVISION_V3 3
#define GAME_REVISION_K 4
#define GAME_REVISION_W 5
#define GAME_REVISION_C 6


// Now define GAME_VERSION, GAME_REGION, and GAME_REVISION symbols set
// to appropriate values for the selected game version.

#if defined(IS_GAME_VERSION_P1_COMPATIBLE)
#define GAME_VERSION GAME_VERSION_P1
#define GAME_REGION GAME_REGION_P
#define GAME_REVISION GAME_REVISION_V1
#elif defined(IS_GAME_VERSION_E1_COMPATIBLE)
#define GAME_VERSION GAME_VERSION_E1
#define GAME_REGION GAME_REGION_E
#define GAME_REVISION GAME_REVISION_V1
#elif defined(IS_GAME_VERSION_J1_COMPATIBLE)
#define GAME_VERSION GAME_VERSION_J1
#define GAME_REGION GAME_REGION_J
#define GAME_REVISION GAME_REVISION_V1
#elif defined(IS_GAME_VERSION_P2_COMPATIBLE)
#define GAME_VERSION GAME_VERSION_P2
#define GAME_REGION GAME_REGION_P
#define GAME_REVISION GAME_REVISION_V2
#elif defined(IS_GAME_VERSION_E2_COMPATIBLE)
#define GAME_VERSION GAME_VERSION_E2
#define GAME_REGION GAME_REGION_E
#define GAME_REVISION GAME_REVISION_V2
#elif defined(IS_GAME_VERSION_J2_COMPATIBLE)
#define GAME_VERSION GAME_VERSION_J2
#define GAME_REGION GAME_REGION_J
#define GAME_REVISION GAME_REVISION_V2
#elif defined(IS_GAME_VERSION_P3_COMPATIBLE)
#define GAME_VERSION GAME_VERSION_P3
#define GAME_REGION GAME_REGION_P
#define GAME_REVISION GAME_REVISION_V3
#elif defined(IS_GAME_VERSION_J3_COMPATIBLE)
#define GAME_VERSION GAME_VERSION_J3
#define GAME_REGION GAME_REGION_J
#define GAME_REVISION GAME_REVISION_V3
#elif defined(IS_GAME_VERSION_K_COMPATIBLE)
#define GAME_VERSION GAME_VERSION_K
#define GAME_REGION GAME_REGION_K
#define GAME_REVISION GAME_REVISION_K
#elif defined(IS_GAME_VERSION_W_COMPATIBLE)
#define GAME_VERSION GAME_VERSION_W
#define GAME_REGION GAME_REGION_W
#define GAME_REVISION GAME_REVISION_W
#elif defined(IS_GAME_VERSION_C_COMPATIBLE)
#define GAME_VERSION GAME_VERSION_C
#define GAME_REGION GAME_REGION_C
#define GAME_REVISION GAME_REVISION_C
#else  // "DYNAMIC" version is implied by default if unspecified
#ifndef IS_GAME_VERSION_DYNAMIC
#define IS_GAME_VERSION_DYNAMIC
#endif  // IS_GAME_VERSION_DYNAMIC
#define GAME_VERSION GAME_VERSION_DYNAMIC
// GAME_REGION and GAME_REVISION will be left undefined, because you
// should really check for IS_GAME_VERSION_DYNAMIC before attempting to
// do any logic based on the region and/or revision
#endif

#endif // GAME_VERSIONS_NSMBW_H
