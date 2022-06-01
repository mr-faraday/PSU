<script setup>
import { ref } from 'vue'
import SpinnerIndicator from '@/components/SpinnerIndicator.vue'
import ReceiveCargoForm from '@/components/forms/ReceiveCargoForm.vue'
import CargosApi from '@/api/cargos-api'

const loading = ref(false)
const form = ref(null)

const receiveCargo = async (cargoData) => {
  try {
    loading.value = true

    const res = await CargosApi.create(cargoData)
    alert(`Задача на приём ТМЦ создана, id: ${res.data.result.id}`)

    form.value.clearForm()
  } catch (error) {
    if (error.request?.data?.message) {
      alert(error.request.data.message)
    } else {
      console.warn(error)
    }
  } finally {
    loading.value = false
  }
}
</script>

<template>
  <div v-if="loading" class="spinner-container">
    <SpinnerIndicator />
  </div>

  <div v-else class="create-client-form-container">
    <ReceiveCargoForm ref="form" @submit="receiveCargo" />
  </div>
</template>

<style lang="scss" scoped>
</style>
