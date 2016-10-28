#include <err.h>
#include <string.h>
#include <stdlib.h>
#include <jansson.h>

int main()
{
    char* text = "[{\"key1\": \"val1\"}, [\"foo.so\", {\"key1\": \"val1\"}], [\"bar.so\", {\"key1\": \"val1\"}]]";
    json_t* root;
    json_error_t error;
    root = json_loads(text, 0, &error);
    if(!root)
        errx(EXIT_FAILURE, "%s: %u: %s", __FILE__, error.line, error.text);

    if(!json_is_array(root))
    {
        json_decref(root);
        errx(EXIT_FAILURE, "%s: %u: %s", __FILE__, __LINE__, "not an array");
    }

    json_t* data;
    data = json_array_get(root, 0);
    data = json_object_get(data, "key1");
    const char* string;
    string = json_string_value(data);
    printf("%s\n", string);
    json_decref(root);

    return 0;
}

