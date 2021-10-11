
#include "arguments.h"

static struct argp_option options[] = {
    {"debug", 'd', 0, 0, "Enable debug", 1},
    {"low", 'l', "0", 0, "Low interval", 2},
    {"high", 'h', "5", 0, "High interval", 3},
    {0}};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
  struct arguments_s *arguments = state->input;

  switch (key)
  {
  case 'l':
    arguments->low = atoi(arg);
    break;
  case 'h':
    arguments->high = atoi(arg);
    break;
  case 'd':
    arguments->debug = 1;
    break;
  case ARGP_KEY_ARG:
    if (state->arg_num >= 1)
    {
      argp_usage(state);
    }
    arguments->args[state->arg_num] = arg;
    break;
  case ARGP_KEY_END:
    if (state->arg_num == 0)
    {
      argp_usage(state);
    }
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static void set_defaults(arguments_t *arguments)
{
  arguments->separator = " ";
  arguments->debug = 0;
  arguments->low = 0;
  arguments->high = 5;
}

void arguments_process(int argc, char **argv, arguments_t *arguments)
{
  set_defaults(arguments);
  struct argp argp = {options, parse_opt, PORE_ARGS_DOC_ARG, PORE_ARGS_DOC, 0, 0, 0};
  argp_parse(&argp, argc, argv, 0, 0, arguments);
}