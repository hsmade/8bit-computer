#!/usr/bin/env bash
set -euo pipefail

root_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

if ! command -v kicad-cli >/dev/null 2>&1; then
  echo "error: kicad-cli not found in PATH" >&2
  exit 1
fi

if ! command -v zip >/dev/null 2>&1; then
  echo "error: zip not found in PATH" >&2
  exit 1
fi

shopt -s nullglob

boards=()
for dir in "$root_dir"/*/; do
  pcb_files=("$dir"/*.kicad_pcb)
  if (( ${#pcb_files[@]} == 1 )); then
    boards+=("${pcb_files[0]}")
  elif (( ${#pcb_files[@]} > 1 )); then
    echo "warning: skipping $dir because it has multiple .kicad_pcb files" >&2
  fi
done

if (( ${#boards[@]} == 0 )); then
  echo "error: no board directories with .kicad_pcb files found under $root_dir" >&2
  exit 1
fi

for pcb in "${boards[@]}"; do
  board_dir="$(dirname "$pcb")"
  board_name="$(basename "$pcb" .kicad_pcb)"
  out_dir="$board_dir/gerbers"
  zip_file="$out_dir/${board_name}-gerbers.zip"

  echo "==> $board_name"

  rm -rf "$out_dir"
  mkdir -p "$out_dir"

  kicad-cli pcb export gerbers \
    --board-plot-params \
    -o "$out_dir" \
    "$pcb"

  kicad-cli pcb export drill \
    --format excellon \
    --excellon-units mm \
    --excellon-zeros-format decimal \
    --excellon-separate-th \
    --generate-map \
    --map-format gerberx2 \
    -o "$out_dir" \
    "$pcb"

  rm -f "$zip_file"
  (
    cd "$out_dir"
    zip -q "$(basename "$zip_file")" ./*.gbr ./*.gbrjob ./*.drl
  )

  echo "    wrote $zip_file"
done
