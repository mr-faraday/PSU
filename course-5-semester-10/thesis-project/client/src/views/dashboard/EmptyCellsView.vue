<script setup>
import ArchiveApi from '@/api/archive-api'
import { useDataLoader } from '@/hooks/use-data-loader'

const [loading, data] = useDataLoader(() => ArchiveApi.getEmptyCellsCount())
</script>

<template>
  <p>Reuslt: {{ loading ? 'Loading...' : data }}</p>
</template>

