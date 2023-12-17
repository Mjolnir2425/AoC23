#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define PATH "day5.txt"
#define MAX_LEN 250

typedef struct {
    unsigned long long dest_range_start;
    unsigned long long dest_range_end;
    unsigned long long source_range_start;
    unsigned long long source_range_end;
    unsigned long long dest_minus_source;
    unsigned long long range_length;
} MapEntry;

typedef struct {
    unsigned long long seed_range_start;
    unsigned long long seed_range_end;
    unsigned long long seed_range_length;
} SeedInterval;

int get_num_of_seed_intervals() {
    char line[MAX_LEN];

    FILE *fptr = fopen(PATH, "r");
    fgets(line, MAX_LEN, fptr);
    fclose(fptr);

    int i, j, last_index = strlen(line) - 2, num_of_seeds = 0;

    for (i = 6; i < last_index; i++) {
        if (line[i] == ' ') {
            num_of_seeds++;
        }
    }

    return num_of_seeds / 2;
}

unsigned long long n_pow_10(unsigned long long n, int to_pow_10) {
    for (int i = 1; i <= to_pow_10; i++) {
        n *= 10;
    }
    return n;
}

void get_map_sizes(int *seed_len, int *soil_len, int *fert_len, int *water_len,
                   int *light_len, int *temp_len, int *humid_len) {
    char line[MAX_LEN];
    *seed_len = *soil_len = *fert_len = *water_len = *light_len = *temp_len =
        -2;
    *humid_len = -1;

    FILE *fptr = fopen(PATH, "r");

    while (strcmp(line, "seed-to-soil map:\n")) {
        fgets(line, MAX_LEN, fptr);
    }

    while (strcmp(line, "soil-to-fertilizer map:\n")) {
        fgets(line, MAX_LEN, fptr);
        ++*seed_len;
    }

    while (strcmp(line, "fertilizer-to-water map:\n")) {
        fgets(line, MAX_LEN, fptr);
        ++*soil_len;
    }

    while (strcmp(line, "water-to-light map:\n")) {
        fgets(line, MAX_LEN, fptr);
        ++*fert_len;
    }

    while (strcmp(line, "light-to-temperature map:\n")) {
        fgets(line, MAX_LEN, fptr);
        ++*water_len;
    }

    while (strcmp(line, "temperature-to-humidity map:\n")) {
        fgets(line, MAX_LEN, fptr);
        ++*light_len;
    }

    while (strcmp(line, "humidity-to-location map:\n")) {
        fgets(line, MAX_LEN, fptr);
        ++*temp_len;
    }

    while (strcmp(line, "\n")) {
        fgets(line, MAX_LEN, fptr);
        ++*humid_len;
    }
}

void parse_map_string(char *line, MapEntry *map_entry) {
    map_entry->dest_range_start = map_entry->source_range_start =
        map_entry->range_length = 0;

    int last_ind = strlen(line) - 2, i = last_ind;

    while (*(line + i) != ' ') {
        map_entry->range_length += n_pow_10(*(line + i) - '0', last_ind - i);
        i--;
    }
    last_ind = --i;

    while (*(line + i) != ' ') {
        map_entry->source_range_start +=
            n_pow_10(*(line + i) - '0', last_ind - i);
        i--;
    }
    last_ind = --i;

    while (i >= 0) {
        map_entry->dest_range_start +=
            n_pow_10(*(line + i) - '0', last_ind - i);
        i--;
    }

    map_entry->source_range_end =
        map_entry->source_range_start + map_entry->range_length;
    map_entry->dest_range_end =
        map_entry->dest_range_start + map_entry->range_length;
    map_entry->dest_minus_source =
        map_entry->dest_range_start - map_entry->source_range_start;
}

void populate_maps(MapEntry *seed_to_soil_map, int seed_len,
                   MapEntry *soil_to_fert_map, int soil_len,
                   MapEntry *fert_to_water_map, int fert_len,
                   MapEntry *water_to_light_map, int water_len,
                   MapEntry *light_to_temp_map, int light_len,
                   MapEntry *temp_to_humid_map, int temp_len,
                   MapEntry *humid_to_loc_map, int humid_len) {
    char line[MAX_LEN];

    FILE *fptr = fopen(PATH, "r");

    int num_of_lines = seed_len + soil_len + fert_len + water_len + light_len +
                       temp_len + humid_len + 15;

    int i;

    for (i = 0; i < 3; i++) {
        fgets(line, MAX_LEN, fptr);
    }
    for (i = 0; i < seed_len; i++) {
        fgets(line, MAX_LEN, fptr);
        parse_map_string(line, seed_to_soil_map + i);
    }

    for (i = 0; i < 2; i++) {
        fgets(line, MAX_LEN, fptr);
    }
    for (i = 0; i < soil_len; i++) {
        fgets(line, MAX_LEN, fptr);
        parse_map_string(line, soil_to_fert_map + i);
    }

    for (i = 0; i < 2; i++) {
        fgets(line, MAX_LEN, fptr);
    }
    for (i = 0; i < fert_len; i++) {
        fgets(line, MAX_LEN, fptr);
        parse_map_string(line, fert_to_water_map + i);
    }

    for (i = 0; i < 2; i++) {
        fgets(line, MAX_LEN, fptr);
    }
    for (i = 0; i < water_len; i++) {
        fgets(line, MAX_LEN, fptr);
        parse_map_string(line, water_to_light_map + i);
    }

    for (i = 0; i < 2; i++) {
        fgets(line, MAX_LEN, fptr);
    }
    for (i = 0; i < light_len; i++) {
        fgets(line, MAX_LEN, fptr);
        parse_map_string(line, light_to_temp_map + i);
    }

    for (i = 0; i < 2; i++) {
        fgets(line, MAX_LEN, fptr);
    }
    for (i = 0; i < temp_len; i++) {
        fgets(line, MAX_LEN, fptr);
        parse_map_string(line, temp_to_humid_map + i);
    }

    for (i = 0; i < 2; i++) {
        fgets(line, MAX_LEN, fptr);
    }
    for (i = 0; i < humid_len; i++) {
        fgets(line, MAX_LEN, fptr);
        parse_map_string(line, humid_to_loc_map + i);
    }
}

unsigned long long check_map_by_dest(MapEntry *map, int map_len,
                                     unsigned long long dest) {
    bool in_mapped_range = false;
    MapEntry *map_ptr;

    for (int i = 0; i < map_len; i++) {
        map_ptr = map + i;

        if (dest >= map_ptr->dest_range_start &&
            dest < map_ptr->dest_range_end) {
            in_mapped_range = true;
            return dest - map_ptr->dest_minus_source;
        }
    }

    return dest;
}

unsigned long long get_seed_from_loc(
    unsigned long long loc, MapEntry *seed_to_soil_map, int seed_len,
    MapEntry *soil_to_fert_map, int soil_len, MapEntry *fert_to_water_map,
    int fert_len, MapEntry *water_to_light_map, int water_len,
    MapEntry *light_to_temp_map, int light_len, MapEntry *temp_to_humid_map,
    int temp_len, MapEntry *humid_to_loc_map, int humid_len) {
    unsigned long long soil, fert, water, light, temp, humid;

    humid = check_map_by_dest(humid_to_loc_map, humid_len, loc);
    temp = check_map_by_dest(temp_to_humid_map, temp_len, humid);
    light = check_map_by_dest(light_to_temp_map, light_len, temp);
    water = check_map_by_dest(water_to_light_map, water_len, light);
    fert = check_map_by_dest(fert_to_water_map, fert_len, water);
    soil = check_map_by_dest(soil_to_fert_map, soil_len, fert);
    return check_map_by_dest(seed_to_soil_map, seed_len, soil);
}

void set_seed_intervals(SeedInterval *seed_intervals) {
    char line[MAX_LEN];

    FILE *fptr = fopen(PATH, "r");
    fgets(line, MAX_LEN, fptr);
    fclose(fptr);

    int i, j, last_index = strlen(line) - 2, start_i = last_index,
              current_interval = 0, nums_detected = 0;
    unsigned long long num = 0;

    for (i = last_index; i > 5; i--) {
        if (line[i] != ' ') {
            num += n_pow_10(line[i] - '0', start_i - i);
            continue;
        }

        if (nums_detected++ % 2 == 0) {
            (seed_intervals + current_interval)->seed_range_length = num;
        } else {
            (seed_intervals + current_interval)->seed_range_start = num;
            (seed_intervals + current_interval)->seed_range_end =
                num + (seed_intervals + current_interval)->seed_range_length;
            current_interval++;
        }
        num = 0;
        start_i = i - 1;
    }
}

unsigned long long find_lowest_loc(MapEntry *seed_to_soil_map, int seed_len,
                                   MapEntry *soil_to_fert_map, int soil_len,
                                   MapEntry *fert_to_water_map, int fert_len,
                                   MapEntry *water_to_light_map, int water_len,
                                   MapEntry *light_to_temp_map, int light_len,
                                   MapEntry *temp_to_humid_map, int temp_len,
                                   MapEntry *humid_to_loc_map, int humid_len) {
    int i, num_of_seed_intervals = get_num_of_seed_intervals();
    unsigned long long loc = 0, seed;

    SeedInterval seed_intervals[num_of_seed_intervals];
    set_seed_intervals(seed_intervals);

    while (1) {
        seed = get_seed_from_loc(
            loc, seed_to_soil_map, seed_len, soil_to_fert_map, soil_len,
            fert_to_water_map, fert_len, water_to_light_map, water_len,
            light_to_temp_map, light_len, temp_to_humid_map, temp_len,
            humid_to_loc_map, humid_len);
        for (i = 0; i < num_of_seed_intervals; i++) {
            if (seed >= seed_intervals[i].seed_range_start &&
                seed < seed_intervals[i].seed_range_end) {
                return loc;
            }
        }
        loc++;
    }
}

int main(void) {
    int seed_len, soil_len, fert_len, water_len, light_len, temp_len, humid_len;

    get_map_sizes(&seed_len, &soil_len, &fert_len, &water_len, &light_len,
                  &temp_len, &humid_len);

    MapEntry seed_to_soil_map[seed_len];
    MapEntry soil_to_fert_map[soil_len];
    MapEntry fert_to_water_map[fert_len];
    MapEntry water_to_light_map[water_len];
    MapEntry light_to_temp_map[light_len];
    MapEntry temp_to_humid_map[temp_len];
    MapEntry humid_to_loc_map[humid_len];

    populate_maps(seed_to_soil_map, seed_len, soil_to_fert_map, soil_len,
                  fert_to_water_map, fert_len, water_to_light_map, water_len,
                  light_to_temp_map, light_len, temp_to_humid_map, temp_len,
                  humid_to_loc_map, humid_len);

    unsigned long long lowest_loc = find_lowest_loc(
        seed_to_soil_map, seed_len, soil_to_fert_map, soil_len,
        fert_to_water_map, fert_len, water_to_light_map, water_len,
        light_to_temp_map, light_len, temp_to_humid_map, temp_len,
        humid_to_loc_map, humid_len);

    printf("%llu", lowest_loc);

    return 0;
}
