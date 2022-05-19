<script setup>
import ArchiveApi from '@/api/archive-api'
import { useDataFetch } from '@/hooks/use-data-fetch'
import { ref } from 'vue'

const inputText = ref('')
const [loading, data, fetchData] = useDataFetch(() => ArchiveApi.getDocumentSubjectName(inputText))

const submitHandler = (e) => {
  e.preventDefault()
  fetchData()
}
</script>

<template>
  <form @submit="submitHandler">
    <input v-model="inputText" placeholder="Subject..." />
    <input type="submit" value="Submit" />
  </form>
  <p>Reuslt: {{ loading ? 'Loading...' : String(data) }}</p>
</template>


