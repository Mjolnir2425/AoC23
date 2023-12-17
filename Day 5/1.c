#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define PATH "day5.txt"
#define MAX_LEN 250

typedef struct {
    unsigned int dest_range_start;
    unsigned int source_range_start;
    unsigned int range_length;
} MapEntry;

int get_num_of_seeds() {
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

    return num_of_seeds;
}

unsigned int n_pow_10(unsigned int n, int to_pow_10) {
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

int get_seed_loc(unsigned int seed_num, MapEntry *seed_to_soil_map,
                 int seed_len, MapEntry *soil_to_fert_map, int soil_len,
                 MapEntry *fert_to_water_map, int fert_len,
                 MapEntry *water_to_light_map, int water_len,
                 MapEntry *light_to_temp_map, int light_len,
                 MapEntry *temp_to_humid_map, int temp_len,
                 MapEntry *humid_to_loc_map, int humid_len) {
    int i;
    bool in_mapped_range;
    MapEntry *map_ptr;
    unsigned int soil, fert, water, light, temp, humid, loc;

    in_mapped_range = false;
    for (i = 0; i < seed_len; i++) {
        map_ptr = seed_to_soil_map + i;

        if (seed_num >= map_ptr->source_range_start &&
            seed_num < map_ptr->source_range_start + map_ptr->range_length) {
            in_mapped_range = true;
            soil = seed_num + map_ptr->dest_range_start -
                   map_ptr->source_range_start;
            break;
        }
    }
    if (!in_mapped_range) {
        soil = seed_num;
    }

    in_mapped_range = false;
    for (i = 0; i < soil_len; i++) {
        map_ptr = soil_to_fert_map + i;

        if (soil >= map_ptr->source_range_start &&
            soil < map_ptr->source_range_start + map_ptr->range_length) {
            in_mapped_range = true;
            fert =
                soil + map_ptr->dest_range_start - map_ptr->source_range_start;
            break;
        }
    }
    if (!in_mapped_range) {
        fert = soil;
    }

    in_mapped_range = false;
    for (i = 0; i < fert_len; i++) {
        map_ptr = fert_to_water_map + i;

        if (fert >= map_ptr->source_range_start &&
            fert < map_ptr->source_range_start + map_ptr->range_length) {
            in_mapped_range = true;
            water =
                fert + map_ptr->dest_range_start - map_ptr->source_range_start;
            break;
        }
    }
    if (!in_mapped_range) {
        water = fert;
    }

    in_mapped_range = false;
    for (i = 0; i < water_len; i++) {
        map_ptr = water_to_light_map + i;

        if (water >= map_ptr->source_range_start &&
            water < map_ptr->source_range_start + map_ptr->range_length) {
            in_mapped_range = true;
            light =
                water + map_ptr->dest_range_start - map_ptr->source_range_start;
            break;
        }
    }
    if (!in_mapped_range) {
        light = water;
    }

    in_mapped_range = false;
    for (i = 0; i < light_len; i++) {
        map_ptr = light_to_temp_map + i;

        if (light >= map_ptr->source_range_start &&
            light < map_ptr->source_range_start + map_ptr->range_length) {
            in_mapped_range = true;
            temp =
                light + map_ptr->dest_range_start - map_ptr->source_range_start;
            break;
        }
    }
    if (!in_mapped_range) {
        temp = light;
    }

    in_mapped_range = false;
    for (i = 0; i < temp_len; i++) {
        map_ptr = temp_to_humid_map + i;

        if (temp >= map_ptr->source_range_start &&
            temp < map_ptr->source_range_start + map_ptr->range_length) {
            in_mapped_range = true;
            humid =
                temp + map_ptr->dest_range_start - map_ptr->source_range_start;
            break;
        }
    }
    if (!in_mapped_range) {
        humid = temp;
    }

    in_mapped_range = false;
    for (i = 0; i < humid_len; i++) {
        map_ptr = humid_to_loc_map + i;

        if (humid >= map_ptr->source_range_start &&
            humid < map_ptr->source_range_start + map_ptr->range_length) {
            in_mapped_range = true;
            loc =
                humid + map_ptr->dest_range_start - map_ptr->source_range_start;
            break;
        }
    }
    if (!in_mapped_range) {
        loc = humid;
    }

    return loc;
}

int find_lowest_loc(MapEntry *seed_to_soil_map, int seed_len,
                    MapEntry *soil_to_fert_map, int soil_len,
                    MapEntry *fert_to_water_map, int fert_len,
                    MapEntry *water_to_light_map, int water_len,
                    MapEntry *light_to_temp_map, int light_len,
                    MapEntry *temp_to_humid_map, int temp_len,
                    MapEntry *humid_to_loc_map, int humid_len) {
    char line[MAX_LEN];

    FILE *fptr = fopen(PATH, "r");
    fgets(line, MAX_LEN, fptr);
    fclose(fptr);

    int i, j, last_index = strlen(line) - 2, start_i = last_index;
    unsigned int seed_num = 0, seed_loc, min_loc;
    bool loc_set = false;

    for (i = last_index; i > 5; i--) {
        if (line[i] != ' ') {
            seed_num += n_pow_10(line[i] - '0', start_i - i);
            continue;
        }

        seed_loc = get_seed_loc(seed_num, seed_to_soil_map, seed_len,
                                soil_to_fert_map, soil_len, fert_to_water_map,
                                fert_len, water_to_light_map, water_len,
                                light_to_temp_map, light_len, temp_to_humid_map,
                                temp_len, humid_to_loc_map, humid_len);
        if (!loc_set || seed_loc < min_loc) {
            loc_set = true;
            min_loc = seed_loc;
        }

        seed_num = 0;
        start_i = i - 1;
    }

    return min_loc;
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

    int lowest_loc = find_lowest_loc(
        seed_to_soil_map, seed_len, soil_to_fert_map, soil_len,
        fert_to_water_map, fert_len, water_to_light_map, water_len,
        light_to_temp_map, light_len, temp_to_humid_map, temp_len,
        humid_to_loc_map, humid_len);

    printf("%d", lowest_loc);

    return 0;
}
