<script setup>
import { ref } from 'vue'
import SpinnerIndicator from '@/components/SpinnerIndicator.vue'
import ReceiveCargoForm from '@/components/forms/ReceiveCargoForm.vue'
import CargosApi from '@/api/cargos-api'
import { useToast } from 'vue-toastification'

const toast = useToast()

const loading = ref(false)
const form = ref(null)

const receiveCargo = async (cargoData) => {
  try {
    loading.value = true

    const res = await CargosApi.create(cargoData)
    toast.success(`Задача на приём ТМЦ создана, id: ${res.data.result.id}`)

    form.value.clearForm()
  } catch (error) {
    toast.error(error.response?.data?.message ?? error.message)
  } finally {
    loading.value = false
  }
}
</script>

<template>
  <div v-if="loading" class="spinner-container">
    <SpinnerIndicator />
  </div>

  <div v-else class="create-client-form-container container">
    <ReceiveCargoForm ref="form" @submit="receiveCargo" />
  </div>
</template>

<style lang="scss" scoped>
</style>
