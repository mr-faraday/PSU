<script setup>
import { onMounted, ref } from 'vue'
import SpinnerIndicator from '@/components/SpinnerIndicator.vue'
import { useToast } from 'vue-toastification'
import WarehouseApi from '@/api/warehouse-api'

const toast = useToast()

const loading = ref(false)
const rawData = ref(null)

const fetchTasks = async () => {
  try {
    loading.value = true
    const res = await WarehouseApi.getShelfOcupations()
    rawData.value = res.data.result
  } catch (error) {
    toast.error(error.message)
  } finally {
    loading.value = false
  }
}

onMounted(fetchTasks)
</script>

<template>
  <div v-if="loading" class="spinner-container">
    <SpinnerIndicator />
  </div>

  <div v-else class="container">...</div>
</template>

<style lang="scss" scoped>
</style>
