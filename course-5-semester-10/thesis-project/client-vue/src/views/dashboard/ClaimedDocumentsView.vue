<script setup>
import ArchiveApi from '@/api/archive-api'
import { useDataLoader } from '@/hooks/use-data-loader'

const [loading, data] = useDataLoader(() => ArchiveApi.getClaimedDocuments(), [])
</script>

<template>
  <p>Reuslt: {{ loading ? 'Loading...' : '\n' + data.join('\n') }}</p>
</template>

