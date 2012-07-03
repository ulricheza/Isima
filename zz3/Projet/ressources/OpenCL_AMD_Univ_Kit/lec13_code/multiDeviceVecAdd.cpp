// System includes
#include <stdio.h>
#include <stdlib.h>

// OpenCL includes
#include <CL/cl.h>

// Project includes

// Constants, globals
const int ELEMENTS = 64;   // elements in each vector

// Signatures
char* readSource(const char *sourceFilename); 

int main(int argc, char ** argv)
{
   printf("Running Vector Addition program\n\n");
   //----------------------------------------------------------------
   // Host code
   //----------------------------------------------------------------
   size_t datasize = sizeof(int)*ELEMENTS;

   int *A, *B;   // Input arrays
   int *C;       // Output array

   // Allocate space for input/output data
   A = (int*)malloc(datasize);
   B = (int*)malloc(datasize);
   C = (int*)malloc(datasize);
   if(A == NULL || B == NULL || C == NULL) {
      perror("malloc");
      exit(-1);
   }

   // Initialize the input data
   for(int i = 0; i < ELEMENTS; i++) {
      A[i] = i;
      B[i] = i;
   }

   cl_int status;  // use as return value for most OpenCL functions

   cl_uint numPlatforms = 0;
   cl_platform_id *platforms;
                
   // Query for the number of recongnized platforms
   status = clGetPlatformIDs(0, NULL, &numPlatforms);
   if(status != CL_SUCCESS) {
      printf("clGetPlatformIDs failed\n");
      exit(-1);
   }

   // Make sure some platforms were found 
   if(numPlatforms == 0) {
      printf("No platforms detected.\n");
      exit(-1);
   }

   // Allocate enough space for each platform
   platforms = (cl_platform_id*)malloc(numPlatforms*sizeof(cl_platform_id));
   if(platforms == NULL) {
      perror("malloc");
      exit(-1);
   }

   // Fill in platforms
   clGetPlatformIDs(numPlatforms, platforms, NULL);
   if(status != CL_SUCCESS) {
      printf("clGetPlatformIDs failed\n");
      exit(-1);
   }

   // Print out some basic information about each platform
   printf("%u platforms detected\n", numPlatforms);
   for(unsigned int i = 0; i < numPlatforms; i++) {
      char buf[100];
      printf("Platform %u: \n", i);
      status = clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR,
                       sizeof(buf), buf, NULL);
      printf("\tVendor: %s\n", buf);
      status |= clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME,
                       sizeof(buf), buf, NULL);
      printf("\tName: %s\n", buf);

      if(status != CL_SUCCESS) {
         printf("clGetPlatformInfo failed\n");
         exit(-1);
      }
   }
   printf("\n");

   cl_uint numDevices = 0;
   cl_device_id *devices;

   // Retrive the number of devices present
   status = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, 0, NULL, 
                           &numDevices);
   if(status != CL_SUCCESS) {
      printf("clGetDeviceIDs failed\n");
      exit(-1);
   }

   // Make sure at least 2 devices were found
   if(numDevices < 2) {
      printf("Not enough devices detected (%d found, need 2).\n", numDevices);
      exit(-1);
   }

   // Allocate enough space for each device
   devices = (cl_device_id*)malloc(numDevices*sizeof(cl_device_id));
   if(devices == NULL) {
      perror("malloc");
      exit(-1);
   }

   // Fill in devices
   status = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, numDevices,
                     devices, NULL);
   if(status != CL_SUCCESS) {
      printf("clGetDeviceIDs failed\n");
      exit(-1);
   }   

   // Print out some basic information about each device
   printf("%u devices detected\n", numDevices);
   for(unsigned int i = 0; i < numDevices; i++) {
      char buf[100];
      printf("Device %u: \n", i);
      status = clGetDeviceInfo(devices[i], CL_DEVICE_VENDOR,
                       sizeof(buf), buf, NULL);
      printf("\tDevice: %s\n", buf);
      status |= clGetDeviceInfo(devices[i], CL_DEVICE_NAME,
                       sizeof(buf), buf, NULL);
      printf("\tName: %s\n", buf);

      if(status != CL_SUCCESS) {
         printf("clGetDeviceInfo failed\n");
         exit(-1);
      }
   }
   printf("\n");

   cl_context context;

   // Create a context and associate it with the devices
   context = clCreateContext(NULL, numDevices, devices, NULL, NULL, &status);
   if(status != CL_SUCCESS || context == NULL) {
      printf("clCreateContext failed\n");
      exit(-1);
   }

   cl_command_queue cmdQueue0, cmdQueue1;

   // Create a command queue and associate it with the device you 
   // want to execute on
   cmdQueue0 = clCreateCommandQueue(context, devices[0], 0, &status);
   if(status != CL_SUCCESS || cmdQueue0 == NULL) {
      printf("clCreateCommandQueue failed\n");
      exit(-1);
   }
   cmdQueue1 = clCreateCommandQueue(context, devices[1], 0, &status);
   if(status != CL_SUCCESS || cmdQueue1 == NULL) {
      printf("clCreateCommandQueue failed\n");
      exit(-1);
   }

   cl_mem d_A0, d_A1, d_B0, d_B1;  // Input buffers on devices
   cl_mem d_C0, d_C1;              // Output buffers on devices

   d_A0 = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, 
                         datasize/2, A, &status);
   if(status != CL_SUCCESS || d_A0 == NULL) {
      printf("clCreateBufferA0 failed\n");
      exit(-1);
   }
   d_A1 = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, 
                         datasize/2, &A[ELEMENTS/2], &status);
   if(status != CL_SUCCESS || d_A1 == NULL) {
      printf("clCreateBufferA1 failed\n");
      exit(-1);
   }
   d_B0 = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, 
                         datasize/2, B, &status);
   if(status != CL_SUCCESS || d_B0 == NULL) {
      printf("clCreateBufferB0 failed\n");
      exit(-1);
   }
   d_B1 = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, 
                         datasize/2, &B[ELEMENTS/2], &status);
   if(status != CL_SUCCESS || d_B1 == NULL) {
      printf("clCreateBufferB1 failed\n");
      exit(-1);
   }
   d_C0 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, datasize/2, NULL, &status);
   if(status != CL_SUCCESS || d_C0 == NULL) {
      printf("clCreateBufferC0 failed\n");
      exit(-1);
   }
   d_C1 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, datasize/2, NULL, &status);
   if(status != CL_SUCCESS || d_C1 == NULL) {
      printf("clCreateBufferC1 failed\n");
   }


   cl_program program;
   
   char *source;
   const char *sourceFile = "vectoradd.cl";
   // This function reads in the source code of the program
   source = readSource(sourceFile);

   //printf("Program source is:\n%s\n", source);

   // Create a program. The 'source' string is the code from the 
   // vectoradd.cl file.
   program = clCreateProgramWithSource(context, 1, (const char**)&source, 
                              NULL, &status);
   if(status != CL_SUCCESS) {
      printf("clCreateProgramWithSource failed\n");
      exit(-1);
   }

   cl_int buildErr;
   // Build (compile & link) the program for the devices.
   // Save the return value in 'buildErr' (the following 
   // code will print any compilation errors to the screen)
   buildErr = clBuildProgram(program, numDevices, devices, NULL, NULL, NULL);

   // If there are build errors, print them to the screen
   if(buildErr != CL_SUCCESS) {
      printf("Program failed to build.\n");
      cl_build_status buildStatus;
      for(unsigned int i = 0; i < numDevices; i++) {
         clGetProgramBuildInfo(program, devices[i], CL_PROGRAM_BUILD_STATUS,
                          sizeof(cl_build_status), &buildStatus, NULL);
         if(buildStatus == CL_SUCCESS) {
            continue;
         }

         char *buildLog;
         size_t buildLogSize;
         clGetProgramBuildInfo(program, devices[i], CL_PROGRAM_BUILD_LOG,
                          0, NULL, &buildLogSize);
         buildLog = (char*)malloc(buildLogSize);
         if(buildLog == NULL) {
            perror("malloc");
            exit(-1);
         }
         clGetProgramBuildInfo(program, devices[i], CL_PROGRAM_BUILD_LOG,
                          buildLogSize, buildLog, NULL);
         buildLog[buildLogSize-1] = '\0';
         printf("Device %u Build Log:\n%s\n", i, buildLog);   
         free(buildLog);
      }
      exit(0);
   }
   else {
      printf("No build errors\n");
   }


   cl_kernel kernel0, kernel1;

   // Create a kernel from the vector addition function (named "vecadd")
   kernel0 = clCreateKernel(program, "vecadd", &status);
   if(status != CL_SUCCESS) {
      printf("clCreateKernel failed\n");
      exit(-1);
   }
   kernel1 = clCreateKernel(program, "vecadd", &status);
   if(status != CL_SUCCESS) {
      printf("clCreateKernel failed\n");
      exit(-1);
   }

   // Associate the input and output buffers with the kernels 
   status  = clSetKernelArg(kernel0, 0, sizeof(cl_mem), &d_A0);
   status |= clSetKernelArg(kernel0, 1, sizeof(cl_mem), &d_B0);
   status |= clSetKernelArg(kernel0, 2, sizeof(cl_mem), &d_C0);
   if(status != CL_SUCCESS) {
      printf("clSetKernelArg failed\n");
      exit(-1);
   }

   status  = clSetKernelArg(kernel1, 0, sizeof(cl_mem), &d_A1);
   status |= clSetKernelArg(kernel1, 1, sizeof(cl_mem), &d_B1);
   status |= clSetKernelArg(kernel1, 2, sizeof(cl_mem), &d_C1);
   if(status != CL_SUCCESS) {
      printf("clSetKernelArg failed\n");
      exit(-1);
   }

   // Define an index space (global work size) of threads for execution.  
   // A workgroup size (local work size) is not required, but can be used.
   size_t globalWorkSize[1];  // There are ELEMENTS threads
   globalWorkSize[0] = ELEMENTS/2;

   // Execute the kernels.
   status = clEnqueueNDRangeKernel(cmdQueue0, kernel0, 1, NULL, globalWorkSize, 
                           NULL, 0, NULL, NULL);
   if(status != CL_SUCCESS) {
      printf("clEnqueueNDRangeKernel0 failed (%d)\n", status);
      exit(-1);
   }
   status = clEnqueueNDRangeKernel(cmdQueue1, kernel1, 1, NULL, globalWorkSize, 
                           NULL, 0, NULL, NULL);
   if(status != CL_SUCCESS) {
      printf("clEnqueueNDRangeKernel1 failed (%d)\n", status);
      exit(-1);
   }

   // Read the OpenCL output buffers to the host output array (C)
   clEnqueueReadBuffer(cmdQueue0, d_C0, CL_TRUE, 0, datasize/2, C, 
                       0, NULL, NULL);
   clEnqueueReadBuffer(cmdQueue1, d_C1, CL_TRUE, 0, datasize/2, 
                       &C[ELEMENTS/2], 0, NULL, NULL);

   // Verify correctness
   bool result = true;
   for(int i = 0; i < ELEMENTS; i++) {
      if(C[i] != i+i) {
         result = false;
         break;
      }
   }
   if(result) {
      printf("Output is correct\n");
   }
   else {
      printf("Output is incorrect\n");
   }

   clReleaseKernel(kernel0);
   clReleaseKernel(kernel1);
   clReleaseProgram(program);
   clReleaseCommandQueue(cmdQueue0);
   clReleaseCommandQueue(cmdQueue1);
   clReleaseMemObject(d_A0);
   clReleaseMemObject(d_A1);
   clReleaseMemObject(d_B0);
   clReleaseMemObject(d_B1);
   clReleaseMemObject(d_C0);
   clReleaseMemObject(d_C1);
   clReleaseContext(context);

   free(A);
   free(B);
   free(C);
   free(source);
   free(platforms);
   free(devices);

}

char* readSource(const char *sourceFilename) {

   FILE *fp;
   int err;
   int size;

   char *source;

   fp = fopen(sourceFilename, "rb");
   if(fp == NULL) {
      printf("Could not open kernel file: %s\n", sourceFilename);
      exit(-1);
   }
   
   err = fseek(fp, 0, SEEK_END);
   if(err != 0) {
      printf("Error seeking to end of file\n");
      exit(-1);
   }

   size = ftell(fp);
   if(size < 0) {
      printf("Error getting file position\n");
      exit(-1);
   }

   err = fseek(fp, 0, SEEK_SET);
   if(err != 0) {
      printf("Error seeking to start of file\n");
      exit(-1);
   }

   source = (char*)malloc(size+1);
   if(source == NULL) {
      printf("Error allocating %d bytes for the program source\n", size+1);
      exit(-1);
   }

   err = fread(source, 1, size, fp);
   if(err != size) {
      printf("only read %d bytes\n", err);
      exit(0);
   }

   source[size] = '\0';

   return source;
}
