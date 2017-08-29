#!/usr/bin/env groovy

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

parallel rocm_fiji: {

  currentBuild.result = "SUCCESS"
  node('rocm-1.6 && fiji')
  {
    def scm_dir = pwd()
    def build_dir_debug = "${scm_dir}/test/debug"
    def build_dir_release = "${scm_dir}/test/release"

    // Run the containers preperation script
    // Note, exported environment variables do not live outside of sh step
    sh ". /home/jenkins/prep-env.sh"

    // The following try block performs build steps
    try
    {
      dir("${scm_dir}") {
        stage("Clone") {
          checkout scm
        }
      }

      withEnv(["PATH=${PATH}:/opt/rocm/bin"]) {
        // Record important versions of software layers we use
        sh '''clang++ --version
              cmake --version
              hcc --version
              hipconfig --version
           '''

        // install Tensile
        dir("${scm_dir}") {
          sh '''
            pwd
            ls -l
            sudo apt-get update
            sudo apt-get install python-setuptools
            sudo python setup.py install
          '''
        }

        // run jenkins tests
        dir("${build_dir_release}") {
          stage("unit tests") {

           // defaults
           sh "tensile ../../Tensile/Configs/test_hgemm_defaults.yaml hgemm_defaults"
           sh "tensile ../../Tensile/Configs/test_sgemm_defaults.yaml sgemm_defaults"
           sh "tensile ../../Tensile/Configs/test_dgemm_defaults.yaml dgemm_defaults"

           // thorough tests
           sh "tensile --runtime-language=HIP --kernel-language=HIP ../../Tensile/Configs/test_hgemm.yaml hgemm"
           sh "tensile --runtime-language=HIP --kernel-language=HIP ../../Tensile/Configs/test_sgemm.yaml sgemm"

           // vectors
           sh "tensile --runtime-language=HIP --kernel-language=HIP ../../Tensile/Configs/test_hgemm_vectors.yaml hgemm_vectors"
           sh "tensile --runtime-language=HIP --kernel-language=HIP ../../Tensile/Configs/test_sgemm_vectors.yaml sgemm_vectors"

           // assembly
           sh "tensile ../../Tensile/Configs/sgemm_gfx803.yaml sgemm_gfx803"

           // TODO re-enable when jenkins supports opencl
           //sh "tensile --runtime-language=OCL --kernel-language=OCL ../../Tensile/Configs/test_sgemm_vectors.yaml sgemm_vectors"
          }
        }
      }
    }
    catch( err )
    {
      currentBuild.result = "FAILURE"
      throw err
    }
  } // node
}
