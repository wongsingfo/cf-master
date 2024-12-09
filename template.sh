#!/usr/bin/env bash

set -e
set -o pipefail

MODEL=claude-3-opus-20240229
MODEL=claude-3-5-sonnet-20240620
MODEL=gpt-4o-2024-08-06
MODEL=yi-large

PROMPT_INPUT="Extract all example input data from the problem statement.
DO NOT include the example output data. Response ONLY with data in a code block."

PROMPT_OUTPUT="Extract all example output data from the problem statement.
DO NOT include the example input data. Response ONLY with data in a code block."

LANG=cpp
OUTPUT_CODE=a.${LANG}

LLM_CLI=${HOME}/dotfiles/chatgpt.sh

if [ -n "$1" ]; then
	LANG=$1
fi

if [ ! -f "$LLM_CLI" ] ; then
	echo "Cannot find language model CLI tool: $LLM_CLI"
	echo "Possible implementations:"
	echo "  https://github.com/wongsingfo/dotfiles/blob/master/chatgpt.sh"
	echo "  https://llm.datasette.io/en/stable/"
	echo
	echo "You may need to adapt this script after installing the CLI tool."
	exit 1
fi

# echo "Please paste your problem here (CTRL+D to finish):"
# cat >problem.txt

echo "Generating template..."
echo "// Created at:" $(date) > "$OUTPUT_CODE"
cat "template.md" problem.txt |
	"$LLM_CLI" --model "$MODEL" --stdin |
	stdbuf -oL tee /dev/stderr |
	stdbuf -oL awk '/```/{flag=!flag;next} flag{print}' >> "$OUTPUT_CODE"

echo "Parsing input..."
cat problem.txt |
	"$LLM_CLI" --stdin "$PROMPT_INPUT" |
	tee /dev/stderr |
	awk '/```/{flag=!flag;next} flag{print}' > in.txt


echo "Parsing output..."
cat problem.txt |
	"$LLM_CLI" --stdin "$PROMPT_OUTPUT" |
	tee /dev/stderr |
	awk '/```/{flag=!flag;next} flag{print}' > ans.txt
