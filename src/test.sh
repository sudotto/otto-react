#!/bin/bash
echo $(sox -t alsa default -n trim 0 0.01 stat 2>&1 | grep -E 'Mean[[:space:]]+amplitude' | rev | cut -c1-6 | rev)
