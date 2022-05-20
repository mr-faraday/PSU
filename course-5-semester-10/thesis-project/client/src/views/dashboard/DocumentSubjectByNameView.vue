<script setup>
import ArchiveApi from '@/api/archive-api'
import { useDataFetch } from '@/hooks/use-data-fetch'
import { ref } from 'vue'

const inputText = ref('')
const [loading, data, fetchData] = useDataFetch(() => ArchiveApi.getDocumentSubjectName(inputText.value), '')

const submitHandler = (e) => {
  e.preventDefault()
  fetchData()
}
</script>

<template>
  <form @submit="submitHandler">
    <input v-model="inputText" placeholder="Document name..." />
    <input type="submit" value="Submit" />
  </form>
  <p>Reuslt: {{ loading ? 'Loading...' : data }}</p>
</template>

