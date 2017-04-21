/*******************************************************************************
* Copyright (C) 2016 Advanced Micro Devices, Inc. All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell cop-
* ies of the Software, and to permit persons to whom the Software is furnished
* to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IM-
* PLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
* FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
* IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNE-
* CTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************************/

#include "TensileTypes.h"
#include "SolutionHelper.h"

#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>

/*******************************************************************************
 * tensileSetup()
 ******************************************************************************/
TensileStatus tensileSetup() {
  return tensileStatusSuccess;
}


/*******************************************************************************
 * tensileTeardown
 ******************************************************************************/
TensileStatus tensileTeardown() {

#if Tensile_RUNTIME_LANGUAGE_OCL
  // delete kernels
  if (kernelMap) {
    unsigned int index = 0;
    for ( KernelMap::iterator i = kernelMap->begin(); i != kernelMap->end(); i++) {
      // printf("releasing kernel %u\n", index);
      clReleaseKernel(i->second);
      index++;
    }
    delete kernelMap;
    kernelMap = NULL;
  }
#endif
  return tensileStatusSuccess;
}
