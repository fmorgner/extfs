#!/usr/bin/env bash

set -e

echo "Reporting coverage to Coveralls.io ..."

while read FILENAME; do
  LCOV_INPUT_FILES="$LCOV_INPUT_FILES -a \"$FILENAME\""
done < <( find Coverage -name *.clean )

eval lcov "${LCOV_INPUT_FILES}" -o Coverage/coverage.info
sed -i'' -e "s_$(cd .. && pwd)/__g" Coverage/coverage.info

cd ..
coveralls-lcov --repo-token ${COVERALLS_API_TOKEN} build/Coverage/coverage.info
