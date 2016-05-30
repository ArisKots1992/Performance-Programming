#!/bin/bash
# This script helps when we execute in the morar machine to delete every other result, so we have the final
# results availiable only
rm  bench_c.sge.*

qsub bench_c.sge
