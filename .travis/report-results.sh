#!/usr/bin/env bash

set -e

cd ${TRAVIS_BUILD_DIR}

for report in $(find . -iname '*_test.xml'); do
  echo "Publishing results from ${report}"
  curl -X PUT \
    -H "Authorization: Token ${JUNIT_REPORTING_TOKEN}" \
    -H "Content-Disposition: attachement; filename=${report}" \
    --upload-file ${report} \
    ${JUNIT_REPORTING_HOST}/p/extfs/upload/${TRAVIS_BUILD_NUMBER}
done
