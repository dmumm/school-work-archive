#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <assert.h>

typedef struct {
    unsigned char presence; /* could be single bit */
    unsigned char pfn;      /* 8 bits */
} PTE_t;

typedef struct {
    unsigned short valid;   /* could be single bit, short for padding */
    unsigned short vpn;     /* 16 bits */
    unsigned int time_stamp;/* 32 bits for true-LRU replacement */
} CME_t;

typedef struct {
    unsigned short vpn;     /* 16 bits */
    unsigned char valid;    /* could be single bit */
    unsigned char pfn;      /* 8 bits */
    unsigned int time_stamp;/* 32 bits for true-LRU replacement */
} TLBE_t;

// Configuration Parameters
int num_virtual_pages;   // number of virtual pages
int num_page_frames;   // number of page frames
int tlb_entries;   // number of TLB entries
int verbose;

// Simulation Data Structures
PTE_t * page_table;
CME_t * core_map;
TLBE_t * tlb;

// Simulation Counters
unsigned int access_count = 0;
unsigned int tlb_misses = 0;
unsigned int page_faults = 0;

// constants

#define NO_FREE_FRAME -1
#define NO_VALID_FRAME -1


void read_config()
{
    FILE * cfg_file = fopen("paging.cfg", "r");
    if (!cfg_file) {
        printf("error in opening configuration file\n");
        exit(EXIT_FAILURE);
    }

    if (fscanf(cfg_file, "VP %d\nPF %d\nTE %d", &num_virtual_pages, &num_page_frames, &tlb_entries) != 3) {
        printf("error in reading configuration file\n");
        fclose(cfg_file);
        exit(EXIT_FAILURE);
    }

    if (num_virtual_pages <= 0) {
        printf("VP (virtual pages) = %d is out of range\n", num_virtual_pages);
        fclose(cfg_file);
        exit(EXIT_FAILURE);
    }
    if (num_page_frames <= 0) {
        printf("PF (page frames) = %d is out of range\n", num_page_frames);
        fclose(cfg_file);
        exit(EXIT_FAILURE);
    }
    if (tlb_entries <= 0) {
        printf("TE (tlb entries) = %d is out of range\n", tlb_entries);
        fclose(cfg_file);
        exit(EXIT_FAILURE);
    }

    fclose(cfg_file);
    if (verbose) {
        printf("paging simulation\n");
        printf("  %d virtual pages in the virtual address space\n", num_virtual_pages);
        printf("  %d physical page frames\n", num_page_frames);
        printf("  %d TLB entries\n", tlb_entries);
    }
}


void initialize_simulation()
{
    page_table = malloc(num_virtual_pages * sizeof(PTE_t));
    core_map = malloc(num_page_frames * sizeof(CME_t));
    tlb = malloc(tlb_entries * sizeof(TLBE_t));

    for (int i = 0; i < num_virtual_pages; i++) {
        page_table[i].presence = 0;
        page_table[i].pfn = 0;
    }
    for (int i = 0; i < num_page_frames; i++) {
        core_map[i].valid = 0;
        core_map[i].vpn = 0;
        core_map[i].time_stamp = 0;
    }
    for (int i = 0; i < tlb_entries; i++) {
        tlb[i].valid = 0;
        tlb[i].vpn = 0;
        tlb[i].pfn = 0;
        tlb[i].time_stamp = 0;
    }
}

int check_TLB(unsigned short vpn);
int check_page_table(unsigned short vpn);
int evict_frame();
void print_final_status();
int handle_page_fault(unsigned short vpn);
void update_TLB(unsigned short vpn, unsigned char pfn);


void debug_print()
{
    printf("statistics\n");
    printf("  accesses    = %d\n", access_count);
    printf("  tlb misses  = %d\n", tlb_misses);
    printf("  page faults = %d\n", page_faults);
}

// Function to check for an existing vpn::pfn mapping in the TLB
unsigned int tlb_access(unsigned int vpn, unsigned int * pfn)
{
    for (int i = 0; i < tlb_entries; i++) {
        if (tlb[i].valid && tlb[i].vpn == vpn) {
            *pfn = tlb[i].pfn;  // Set the output parameter to the PFN found
            return 1;  // Return 1 for a TLB hit
        }
    }
    return 0;  // Return 0 for a TLB miss
}

int main(int argc, char * argv[])
{
    verbose = 0;
    if (argc > 1 && strcmp(argv[1], "-v") == 0) {
        verbose = 1;
    }


    read_config();
    initialize_simulation();

    char input[7]; // Buffer to hold the input virtual addresses (up to 6 hex digits)
    unsigned int virtual_address;
    unsigned short vpn;
    unsigned char offset;
    int pfn, physical_address;
    int trigger = 0;

    while (scanf("%x", &virtual_address) == 1) {
        access_count++;  // Correctly track the number of accesses

        vpn = (virtual_address >> 8) & 0xFFFF;
        offset = virtual_address & 0xFF;
        if (verbose) {
            printf("access %d:\n", access_count);
            printf("  virtual address is              0x%06x\n", virtual_address);
        }

        if (vpn > num_virtual_pages) {
            trigger++;
            continue;
        }

        pfn = check_TLB(vpn);
        if (pfn == -1) { // TLB miss
            if (verbose) {
                printf("  tlb miss\n");
            }
            pfn = check_page_table(vpn);
            if (pfn == -1) {
                if (verbose) {
                    printf("  page fault\n");

                }

                pfn = handle_page_fault(vpn);
            }
        }
        else {
            printf("  tlb hit\n");
        }

        physical_address = (pfn << 8) | offset;
        if (verbose) {
            printf("0x%04x\n", physical_address);

        }
        update_TLB(vpn, pfn); // Ensure TLB is updated on every access
        if (verbose) {
            printf("  tlb update of vpn 0x%04x with pfn 0x%02x\n", vpn, pfn);
        }


    }

    if (verbose) {
        printf("\n");
    }

    debug_print();

    if (verbose || trigger) {
        print_final_status();
    }

    if (trigger) {
        debug_print();
    }


    free(page_table);
    free(core_map);
    free(tlb);
    return 0;
}

// TLB time stamp for LRU tracking
void update_TLB_time_stamp(int tlb_index)
{
    tlb[tlb_index].time_stamp = access_count;
}

// returns the PFN if found, -1 otherwise
int check_TLB(unsigned short vpn)
{
    if (verbose) {
    }

    int tlb_hit_index = -1;
    unsigned int oldest_time_stamp = UINT_MAX;
    int lru_index = -1;

    for (int i = 0; i < tlb_entries; i++) {
        if (tlb[i].valid && tlb[i].vpn == vpn) {
            tlb_hit_index = i;
            break;
        }
        if (tlb[i].valid && tlb[i].time_stamp < oldest_time_stamp) {
            oldest_time_stamp = tlb[i].time_stamp;
            lru_index = i;
        }
        if (!tlb[i].valid && lru_index == -1) {
            lru_index = i;
        }
    }

    if (tlb_hit_index != -1) {
        if (verbose) {
            printf("  tlb hit, physical address is 0x%04x\n", (tlb[tlb_hit_index].pfn << 8) | (vpn & 0xFF));
        }
        update_TLB_time_stamp(tlb_hit_index);
        return tlb[tlb_hit_index].pfn; // TLB hit, return the PFN
    }
    else {
        tlb_misses++;
        if (verbose) {
            // printf("  tlb miss\n");
        }
        return -1; // TLB miss, indicate failure to find the entry
    }
}

void update_TLB(unsigned short vpn, unsigned char pfn)
{
    int found = 0;
    for (int i = 0; i < tlb_entries; i++) {
        if (tlb[i].valid && tlb[i].vpn == vpn) {
            tlb[i].pfn = pfn; // Update the PFN
            tlb[i].time_stamp = access_count; // Update the timestamp
            found = 1;
            break;
        }
    }
    if (!found) {
        int lru_index = -1;
        unsigned int oldest_time_stamp = UINT_MAX;
        for (int i = 0; i < tlb_entries; i++) {
            if (!tlb[i].valid) {
                lru_index = i;
                break;
            }
            else if (tlb[i].time_stamp < oldest_time_stamp) {
                oldest_time_stamp = tlb[i].time_stamp;
                lru_index = i;
            }
        }
        if (lru_index != -1) {
            tlb[lru_index].vpn = vpn;
            tlb[lru_index].pfn = pfn;
            tlb[lru_index].valid = 1;
            tlb[lru_index].time_stamp = access_count;
        }
    }
}

int find_free_frame()
{
    for (int i = 0; i < num_page_frames; i++) {
        if (0 == core_map[i].valid) {
            return i;
        }
    }
    return NO_FREE_FRAME; // No free frame found
}

// Handle a page fault, including possible eviction if no free frames are available
int handle_page_fault(unsigned short vpn)
{
    // Verbose output to indicate a page fault has occurred
    if (verbose) {
        printf("  page fault\n");
    }

    // Attempt to find a free frame
    int frame_index = find_free_frame();

    // Check if a free frame was not available
    if (frame_index == NO_FREE_FRAME) {
        // Verbose output to indicate that page replacement is needed
        if (verbose) {
            printf("  page replacement needed\n");
        }


        // Evict the least recently used frame
        frame_index = evict_frame();

        // Check if no frame could be evicted
        if (frame_index == NO_VALID_FRAME) {
            fprintf(stderr, "Error: No frame available for eviction.\n");
            exit(EXIT_FAILURE);
        }

    }
    else {
        // Verbose output to indicate that a free frame was found
        if (verbose) {
            printf("  place in empty frame %d\n", frame_index);
        }
    }

    // Update the page table entry for this VPN
    page_table[vpn].presence = 1;
    page_table[vpn].pfn = (unsigned char)frame_index;

    // Update the core map for this frame
    core_map[frame_index].vpn = vpn;
    core_map[frame_index].valid = 1;
    core_map[frame_index].time_stamp = access_count;

    // Update the TLB with the new mapping
    // update_TLB(vpn, (unsigned char)frame_index);

    // Return the frame index where the page was loaded
    return frame_index;
}



// Check the page table for the given VPN and handle the page hit or fault
int check_page_table(unsigned short vpn)
{
    if (page_table[vpn].presence) {
        // Handle page hit
        unsigned char pfn = page_table[vpn].pfn;

        // Update core map time stamp for LRU
        for (int i = 0; i < num_page_frames; i++) {
            if (core_map[i].vpn == vpn && core_map[i].valid) {
                core_map[i].time_stamp = access_count;
                break;
            }
        }

        if (verbose) {
            printf("  page hit, physical address is     ");
        }

        return pfn; // Return the PFN for the physical address calculation
    }
    else {
        // Increment page faults counter
        page_faults++;

        // Handle page fault (includes finding free frame or evicting one)
        int frame_index = handle_page_fault(vpn);
        if (frame_index == -1) {
            fprintf(stderr, "Failed to handle page fault: no free frame and eviction failed.\n");
            exit(EXIT_FAILURE);
        }
        if (verbose) {
            printf("  physical address is               ");
        }
        return frame_index;
    }
}

// Invalidate a TLB entry for a given VPN
void invalidate_TLB_entry(unsigned short vpn)
{
    if (verbose) {
        printf("  TLB invalidate of vpn 0x%x\n", vpn);
    }
    for (int i = 0; i < tlb_entries; i++) {
        if (tlb[i].vpn == vpn && tlb[i].valid) {
            tlb[i].valid = 0;
            break;
        }
    }
}

// Update page table when a frame is evicted
void update_page_table_for_eviction(unsigned short vpn)
{
    page_table[vpn].presence = 0;
}


// Evict the least recently used frame and return its index
int evict_frame()
{
    unsigned int oldest_time_stamp = UINT_MAX;
    int lru_frame_index = NO_VALID_FRAME;

    // Find the least recently used frame based on time stamp
    for (int i = 0; i < num_page_frames; i++) {
        if (core_map[i].valid && core_map[i].time_stamp < oldest_time_stamp) {
            oldest_time_stamp = core_map[i].time_stamp;
            lru_frame_index = i;
        }
    }

    // Verbose output to indicate which frame was replaced
    if (verbose) {
        printf("  replace frame %d\n", lru_frame_index);
    }

    if (lru_frame_index != NO_VALID_FRAME) {
        unsigned short old_vpn = core_map[lru_frame_index].vpn;

        // Invalidate the old mapping in the page table and TLB
        update_page_table_for_eviction(old_vpn);
        invalidate_TLB_entry(old_vpn);

        // Mark the core map entry as invalid
        core_map[lru_frame_index].valid = 0;
    }

    return lru_frame_index;
}

void print_final_status()
{
    printf("\ntlb entries with valid bit on\n");
    for (int i = 0; i < tlb_entries; i++) {
        if (tlb[i].valid) {
            printf("  vpn = 0x%04x, pfn = 0x%02x, time stamp = %d\n", tlb[i].vpn, tlb[i].pfn, tlb[i].time_stamp);
        }
    }

    printf("\ncore map table\n");
    for (int i = 0; i < num_page_frames; i++) {
        if (core_map[i].valid) {
            printf("  pfn = 0x%02x: valid = 1, vpn = 0x%04x, time stamp = %d\n", i, core_map[i].vpn, core_map[i].time_stamp);
        }
    }

    printf("\nentries of page table with presence bit on\n");
    for (int i = 0; i < num_virtual_pages; i++) {
        if (page_table[i].presence) {
            printf("  vpn = 0x%04x: pfn = 0x%02x\n", i, page_table[i].pfn);
        }
    }
}