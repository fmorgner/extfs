#!/usr/bin/env bash

echo "Reporting coverage to Coveralls.io ..."
echo "travis_fold:start:report-coverage"

set -e

while read FILENAME; do
  LCOV_INPUT_FILES="$LCOV_INPUT_FILES -a \"$FILENAME\""
done < <( find Coverage -name *.clean )

lcov "${LCOV_INPUT_FILES}" -o Coverage/coverage.info
sed -i'' -e "s_$(cd .. && pwd)/__g" Coverage/coverage.info

cd ..
coveralls-lcov --repo-token ${COVERALLS_API_TOKEN} build/Coverage/coverage.info

echo "travis_fold:end:report-coverage"
