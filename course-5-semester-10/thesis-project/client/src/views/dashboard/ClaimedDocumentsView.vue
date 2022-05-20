<script setup>
import ArchiveApi from '@/api/archive-api'
import { useDataLoader } from '@/hooks/use-data-loader'

const [loading, data] = useDataLoader(() => ArchiveApi.getClaimedDocuments(), [])
</script>

<template>
  <p v-if="loading">Loading...</p>

  <template v-else-if="data.lengh > 0">
    <p v-for="item in data" :key="item.id">{{ item.document_name }}</p>
  </template>

  <p v-else>Empty</p>
</template>

