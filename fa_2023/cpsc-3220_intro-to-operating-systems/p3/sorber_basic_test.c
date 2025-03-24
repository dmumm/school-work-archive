#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <time.h>

#define NUMBUFS 15
int bufsizes[NUMBUFS] = {2,3,7,14,65,36,700,12,15,64,128,256,512,1024,6000};

void checkCondition(int condition, const char* message) {
    if (!condition) {
        fprintf(stderr, "Assertion failed: %s\n", message);
        fflush(stderr);
        assert(condition);
    }
}

int main()
{



	uint8_t *bufs[NUMBUFS];

	void * firstbreak = sbrk(0);


	free(NULL); //just for kicks

	for (int i=0; i < NUMBUFS; i++)
	{
		//allocate the next block
		bufs[i] = malloc(bufsizes[i]);
		assert(bufs[i] != NULL); //should never return NULL

		//write some data into the buffer
		memset(bufs[i], i, bufsizes[i]);
	}

	void * midbreak = sbrk(0);
	assert(firstbreak == midbreak);

	for (int i=0; i < NUMBUFS; i++)
	{
		//check whether or not the memory is still intact
		for (int b=0; b < bufsizes[i]; b++)
		{
			assert (bufs[i][b] == i);
		}

		free(bufs[i]);
	}

	void * lastbreak = sbrk(0);

	//verify that the program break never moved up.
	assert (firstbreak == lastbreak);


    //== Custom Tests: Small Object Freeing ==//
    const int test_size = 512; // Example size less than 1024
    uint8_t* buffer = (uint8_t*)malloc(test_size);
    assert(buffer != NULL);

    memset(buffer, 0xAA, test_size);

    free(buffer);

    `//TODO: check if block added to freelist

    //= Test calloc =//
    for (int i = 0; i < NUMBUFS; i++) {
        bufs[i] = calloc(bufsizes[i], sizeof(uint8_t));
        // fprintf(stderr, "bufs[%d] = %p\n", i, bufs[i]);
        checkCondition(bufs[i] != NULL, "bufs[i] != NULL"); // Check for successful allocation

        // Verify that the memory is initialized to zero
        for (int b = 0; b < bufsizes[i]; b++) {
            // fprintf(stderr, "bufs[%d][%d] = %d\n", i, b, bufs[i][b]);
            checkCondition(bufs[i][b] == 0, "bufs[i][b] == 0");
        }
        // fprintf(stderr, "freeing bufs[%d]\n", i);
        free(bufs[i]);
    }

    //= Test realloc =//
    for (int i = 0; i < NUMBUFS; i++) {
        bufs[i] = malloc(bufsizes[i]);
        assert(bufs[i] != NULL);

        // Resize the buffer to double its size
        int new_size = bufsizes[i] * 2;
        bufs[i] = realloc(bufs[i], new_size);
        assert(bufs[i] != NULL);

        // Optionally, write data to the new part of the buffer
        memset(bufs[i] + bufsizes[i], 0xDD, bufsizes[i]);

        free(bufs[i]);
    }


    //== Custom Tests: Boundary Checking ==//
    const int sizes[] = {2000, 3000, 1294, 1295, 1296}; // Boundary sizes
    for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); ++i)
    {
        uint8_t* buffer = (uint8_t*)malloc(sizes[i]);
        assert(buffer != NULL);

        // Write and check data
        memset(buffer, 0xBB, sizes[i]);
        for (int j = 0; j < sizes[i]; ++j)
        {
            assert(buffer[j] == 0xBB);
        }
        // fprintf(stderr, "Boundary Memory Set\n");
        free(buffer);
        // fprintf(stderr, "Boundary Memory Free\n");

    }

    fprintf(stderr, "Boundary Success!\n");
    //== Stochastic Tests: Randomly Allocate and Free ==//
    srand(time(NULL)); // Seed the random number generator

    const int num_allocations = 1000;
    uint8_t* allocations[num_allocations];
    int random_sizes[num_allocations];

    for (int i = 0; i < num_allocations; ++i) {
        random_sizes[i] = rand() % 4000; // Random sizes up to said bytes

        allocations[i] = (uint8_t*)malloc(random_sizes[i]);




        // Optionally write data
        memset(allocations[i], 0xCC, random_sizes[i]);
    }

    fprintf(stderr, "Stochastic Memory Set\n");

    for (int i = 0; i < num_allocations; ++i) {
        free(allocations[i]);
    }

    fprintf(stderr, "Stochastic Memory Free\n");
    fprintf(stderr, "Stochastic Success!\n");

    // Memory corruption test
    for (int i = 0; i < NUMBUFS; i++) {
        bufs[i] = malloc(bufsizes[i]);
        // fprintf(stderr, "bufs[%d] = %p\n", i, bufs[i]);
        checkCondition(bufs[i] != NULL, "bufs[i] != NULL");

        // Write known values to the buffer
        memset(bufs[i], i, bufsizes[i]);

        bufs[i] = realloc(bufs[i], bufsizes[i] * 2);

        // fprintf(stderr, "bufs[%d] = %p\n", i, bufs[i]);
        checkCondition(bufs[i] != NULL, "bufs[i] != NULL");

        // Check if the original values are still intact
        for (int b = 0; b < bufsizes[i]; b++) {
            // fprintf(stderr, "bufs[%d][%d] = %d\n", i, b, bufs[i][b]);
            checkCondition(bufs[i][b] == i, "bufs[i][b] == i");
        }

        free(bufs[i]);
    }
    fprintf(stderr, "Memory Corruption Success!\n");

     // Stochastic Memory Corruption Test with Randomized Deallocation
    srand((unsigned int)time(NULL)); // Seed the random number generator

    const int num_tests = 1000; // Number of random tests
    uint8_t* buffers[num_tests];
    int buffer_sizes[num_tests];
    uint8_t* original_contents[num_tests]; // To store original content for verification

    for (int i = 0; i < num_tests; ++i) {
        buffer_sizes[i] = rand() % 1024 + 1; // Random sizes up to 1024 bytes
        buffers[i] = (uint8_t*)malloc(buffer_sizes[i]);

        fprintf(stderr, "Allocating %d bytes for test index %d\n", buffer_sizes[i], i);
        checkCondition(buffers[i] != NULL, "After malloc, buffers[i] != NULL");

        // Fill with random data and store the original content for verification
        // fprintf(stderr, "original_contents[%d] = (uint8_t*)malloc(buffer_sizes[%d])\n", i, i);
        original_contents[i] = (uint8_t*)malloc(buffer_sizes[i]);
        for (int j = 0; j < buffer_sizes[i]; ++j) {
            // fprintf(stderr, "getting random value for buffers[%d][%d]\n", i, j);
            uint8_t random_value = (uint8_t)(rand() % 256);
            // fprintf(stderr, "setting buffers[%d][%d] & original = %d\n", i, j, random_value);
            buffers[i][j] = random_value;
            original_contents[i][j] = random_value;
        }

        // Randomly resize the buffer
        int new_size = rand() % 2048 + 1; // Random new size up to 2048 bytes

        buffers[i] = (uint8_t*)realloc(buffers[i], new_size);
        checkCondition(buffers[i] != NULL, "After realloc, buffers[i] != NULL"); // Ensure reallocation was successful

        // Validate the contents of the original size
        for (int j = 0; j < (new_size > buffer_sizes[i] ? buffer_sizes[i] : new_size); ++j)
        {
            // fprintf(stderr, "buffers[%d][%d] = %d\n", i, j, buffers[i][j]);
            checkCondition(buffers[i][j] == original_contents[i][j], "Validating contents of og size: buffers[i][j] == original_contents[i][j]");
        }

        free(original_contents[i]); // Free the original content storage
    }

    fprintf(stderr, "Stochastic Memory Corruption Test Allocation Completed Successfully\n");

    // Shuffle the array of buffers for random deallocation order
    for (int i = num_tests - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        uint8_t* temp = buffers[i];
        buffers[i] = buffers[j];
        buffers[j] = temp;
    }

    fprintf(stderr, "Stochastic Memory Corruption Test Shuffled\n");

    // Free the buffers in shuffled order
    for (int i = 0; i < num_tests; ++i) {
        free(buffers[i]);
    }


    fprintf(stderr, "Stochastic Memory Corruption Test Completed Successfully\n");\
    return 0;
}