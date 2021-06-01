#pragma once

#define PROCESS_OVERRIDE_BEHAVIOR   (false)
#define PROCESS_USUAL_BEHAVIOR      (true)

// https://stackoverflow.com/a/4415646
#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
