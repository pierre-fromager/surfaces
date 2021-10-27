
#include "arguments.h"

static struct argp_option options[] = {
    {"debug", 'd', 0, 0, "Enable debug", 1},
    {"verbose", 'v', "5", 0, "Verbose level", 2},
    {"low", 'l', "1", 0, "Low interval", 4},
    {"high", 'h', "2", 0, "High interval", 5},
    {"precision", 'p', "64", 0, "GMP precision", 6},
    {0}};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
  struct arguments_s *arguments = state->input;

  switch (key)
  {
  case 'l':
    arguments->low = atof(arg);
    break;
  case 'h':
    arguments->high = atof(arg);
    break;
  case 'v':
    arguments->verbose = atoi(arg);
    break;
  case 'd':
    arguments->debug = 1;
    break;
  case 'p':
    arguments->precision = (unsigned int)atoi(arg);
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
  arguments->debug = 0;
  arguments->verbose = 5;
  arguments->precision = 64;
  arguments->low = 1;
  arguments->high = 2;
}

void arguments_process(int argc, char **argv, arguments_t *arguments)
{
  set_defaults(arguments);
  struct argp argp = {
      options,
      parse_opt,
      PORE_ARGS_DOC_ARG,
      PORE_ARGS_DOC,
      0,
      0,
      0};
  argp_parse(&argp, argc, argv, 0, 0, arguments);
}