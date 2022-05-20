<script setup>
import ArchiveApi from '@/api/archive-api'
import { useDataLoader } from '@/hooks/use-data-loader'

const [loading, data] = useDataLoader(async () => {
  const { data } = await ArchiveApi.getEmptySpace()
  const { racks, shelfs, cells } = data.result
  return {
    data: {
      result: `Racks: ${racks ?? 'NONE'}\nShelfs: ${shelfs ?? 'NONE'}\nCells: ${cells ?? 'NONE'}`,
    },
  }
})
</script>

<template>
  <p>Reuslt: {{ loading ? 'Loading...' : '\n' + data }}</p>
</template>

